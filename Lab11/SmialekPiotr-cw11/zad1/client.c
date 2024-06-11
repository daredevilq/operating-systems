#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define BUFFER_SIZE 1024

int sockfd;

void *receive_handler(void *arg);
void handle_exit();

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ID> <IP> <PORT>\n", argv[0]);
        return 1;
    }

    char *client_id = argv[1];
    char *ip = argv[2];
    int port = atoi(argv[3]);

    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(sockfd);
        return 1;
    }

    send(sockfd, client_id, strlen(client_id), 0);

    pthread_t receive_tid;
    pthread_create(&receive_tid, NULL, receive_handler, NULL);

    signal(SIGINT, handle_exit);

    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        send(sockfd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "STOP") == 0) {
            break;
        }
    }

    pthread_cancel(receive_tid);
    close(sockfd);
    return 0;
}

void *receive_handler(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int len = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (len <= 0) {
            break;
        }

        buffer[len] = '\0';
        printf("%s\n", buffer);
    }
    return NULL;
}

void handle_exit() {
    send(sockfd, "STOP", 4, 0);
    close(sockfd);
    exit(0);
}
