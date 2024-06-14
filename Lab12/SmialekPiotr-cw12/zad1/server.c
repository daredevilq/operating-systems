#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    struct sockaddr_in addr;
    char id[20];
} client_t;

client_t clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int server_sockfd;

void send_message_to_all(char *message, char *sender_id, struct sockaddr_in *sender_addr);
void send_message_to_one(char *message, char *target_id, char *sender_id);
void list_clients(struct sockaddr_in *client_addr);
void remove_client(struct sockaddr_in *client_addr);
void *handle_client(void *arg);
void *alive_check(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "you must provide: [IP] and [PORT]\n");
        return EXIT_FAILURE;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_addr, client_addr;
    pthread_t tid;

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    if (bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("Server is listening on %s:%d\n", ip, port);

    pthread_create(&tid, NULL, alive_check, NULL);

    while (1) {
        socklen_t client_len = sizeof(client_addr);
        char buffer[BUFFER_SIZE];

        int len = recvfrom(server_sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_len);
        if (len > 0) {
            buffer[len] = '\0';
            handle_client((void*)&client_addr);
        }
    }

    close(server_sockfd);
    return EXIT_SUCCESS;
}

void send_message_to_all(char *message, char *sender_id, struct sockaddr_in *sender_addr) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].addr.sin_port != 0 && strcmp(clients[i].id, sender_id) != 0) {
            sendto(server_sockfd, message, strlen(message), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void send_message_to_one(char *message, char *target_id, char *sender_id) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].addr.sin_port != 0 && strcmp(clients[i].id, target_id) == 0) {
            sendto(server_sockfd, message, strlen(message), 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr));
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void list_clients(struct sockaddr_in *client_addr) {
    pthread_mutex_lock(&clients_mutex);

    char list[BUFFER_SIZE] = "Active clients: ";
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].addr.sin_port != 0) {
            strcat(list, clients[i].id);
            strcat(list, " ");
        }
    }

    sendto(server_sockfd, list, strlen(list), 0, (struct sockaddr*)client_addr, sizeof(*client_addr));

    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(struct sockaddr_in *client_addr) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].addr.sin_addr.s_addr == client_addr->sin_addr.s_addr && clients[i].addr.sin_port == client_addr->sin_port) {
            clients[i].addr.sin_port = 0;
            memset(clients[i].id, 0, sizeof(clients[i].id));
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    struct sockaddr_in client_addr = *(struct sockaddr_in*)arg;
    char buffer[BUFFER_SIZE];
    char client_id[20] = {0};

    socklen_t addr_len = sizeof(client_addr);

    if (recvfrom(server_sockfd, client_id, 20, 0, (struct sockaddr*)&client_addr, &addr_len) <= 0) {
        return NULL;
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].addr.sin_port == 0) {
            clients[i].addr = client_addr;
            strcpy(clients[i].id, client_id);
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    printf("Client %s connected\n", client_id);

    while (1) {
        int len = recvfrom(server_sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (len <= 0) {
            break;
        }

        buffer[len] = '\0';

        if (strncmp(buffer, "LIST", 4) == 0) {
            list_clients(&client_addr);
        } else if (strncmp(buffer, "2ALL", 4) == 0) {
            time_t now = time(NULL);
            char message[BUFFER_SIZE];
            snprintf(message, BUFFER_SIZE, "%s [%s]: %s", client_id, ctime(&now), buffer + 5);
            send_message_to_all(message, client_id, &client_addr);
        } else if (strncmp(buffer, "2ONE", 4) == 0) {
            char target_id[20];
            sscanf(buffer + 5, "%s", target_id);
            time_t now = time(NULL);
            char *message_start = strchr(buffer + 5, ' ') + 1;
            char message[BUFFER_SIZE];
            snprintf(message, BUFFER_SIZE, "%s [%s]: %s", client_id, ctime(&now), message_start);
            send_message_to_one(message, target_id, client_id);
        } else if (strncmp(buffer, "STOP", 4) == 0) {
            break;
        }
    }

    remove_client(&client_addr);
    printf("Client %s disconnected\n", client_id);
    return NULL;
}

void *alive_check(void *arg) {
    while (1) {
        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (clients[i].addr.sin_port != 0) {
                if (sendto(server_sockfd, "ALIVE", 5, 0, (struct sockaddr*)&clients[i].addr, sizeof(clients[i].addr)) <= 0) {
                    clients[i].addr.sin_port = 0;
                    memset(clients[i].id, 0, sizeof(clients[i].id));
                }
            }
        }

        pthread_mutex_unlock(&clients_mutex);
        sleep(20);
    }
    return NULL;
}
