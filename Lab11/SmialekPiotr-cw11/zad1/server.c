#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

//wysylamy sygnal ALIVE do klientow co 20sekund

void send_message_to_all(char *message, char *sender_id);
void send_message_to_one(char *message, char *target_id, char *sender_id);
void list_clients(int sockfd);
void remove_client(int sockfd);
void *handle_client(void *arg);
void *alive_check(void *arg);


typedef struct {
    int sockfd;
    char id[20];
} client_t;

client_t clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "you must provide: [IP] and [PORT]\n");
        return EXIT_FAILURE;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    int server_sockfd;
    struct sockaddr_in server_addr, client_addr;
    pthread_t tid;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_sockfd, 10) < 0;

    printf("Server is listening on %s:%d\n", ip, port);

    pthread_create(&tid, NULL, alive_check, NULL);

    while (1) {
        socklen_t client = sizeof(client_addr);
        int client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client);
        pthread_t client_tid;
        pthread_create(&client_tid, NULL, handle_client, (void*)&client_sockfd);
    }

    close(server_sockfd);
    return EXIT_SUCCESS;
}

void send_message_to_all(char *message, char *sender_id) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].sockfd != 0 && strcmp(clients[i].id, sender_id) != 0) {
            send(clients[i].sockfd, message, strlen(message), 0);
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void send_message_to_one(char *message, char *target_id, char *sender_id) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].sockfd != 0 && strcmp(clients[i].id, target_id) == 0) {
            send(clients[i].sockfd, message, strlen(message), 0);
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void list_clients(int sockfd) {
    pthread_mutex_lock(&clients_mutex);

    char list[BUFFER_SIZE] = "Active clients: ";
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].sockfd != 0) {
            strcat(list, clients[i].id);
            strcat(list, " ");
        }
    }

    send(sockfd, list, strlen(list), 0);

    pthread_mutex_unlock(&clients_mutex);
}

void remove_client(int sockfd) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].sockfd == sockfd) {
            clients[i].sockfd = 0;
            memset(clients[i].id, 0, sizeof(clients[i].id));
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    int client_sockfd = *(int*)arg;
    char buffer[BUFFER_SIZE];
    char client_id[20] = {0};

    if (recv(client_sockfd, client_id, 20, 0) <= 0) {
        close(client_sockfd);
        return NULL;
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i].sockfd == 0) {
            clients[i].sockfd = client_sockfd;
            strcpy(clients[i].id, client_id);
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    printf("Client %s connected\n", client_id);

    while (1) {
        int len = recv(client_sockfd, buffer, BUFFER_SIZE, 0);
        if (len <= 0) {
            break;
        }

        buffer[len] = '\0';

        if (strncmp(buffer, "LIST", 4) == 0) {
            list_clients(client_sockfd);
        } else if (strncmp(buffer, "2ALL", 4) == 0) {
            time_t now = time(NULL);
            char message[BUFFER_SIZE];
            snprintf(message, BUFFER_SIZE, "%s [%s]: %s", client_id, ctime(&now), buffer + 5);
            send_message_to_all(message, client_id);
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

    close(client_sockfd);
    remove_client(client_sockfd);
    printf("Client %s disconnected\n", client_id);
    return NULL;
}

void *alive_check(void *arg) {
    while (1) {
        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (clients[i].sockfd != 0) {
                if (send(clients[i].sockfd, "ALIVE", 5, 0) <= 0) {
                    close(clients[i].sockfd);
                    clients[i].sockfd = 0;
                    memset(clients[i].id, 0, sizeof(clients[i].id));
                }
            }
        }

        pthread_mutex_unlock(&clients_mutex);
        sleep(20);
    }
    return NULL;
}
