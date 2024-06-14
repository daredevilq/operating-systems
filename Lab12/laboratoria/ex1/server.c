#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define IP "127.0.0.1"
#define PORT 3000


//wysylamy sygnal ALIVE do klientow co 20sekund


typedef struct {
    int sockfd;
    char id[20];
} client_t;

client_t clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;


int main() {


    int server_sockfd;
    struct sockaddr_in server_addr, client_addr;
    pthread_t tid;

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP);
    server_addr.sin_port = htons(PORT);

    bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    socklen_t len;
    char buff[1024];
    int n = recvfrom(server_sockfd, (char *)buff, 1024, 0, (struct sockaddr*)&server_addr, &len);

    buff[n] = '\0';

    printf(buff);

    printf("Zamykam server\n");

    close(server_sockfd);
    return EXIT_SUCCESS;
}
