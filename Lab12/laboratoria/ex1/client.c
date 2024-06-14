#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define IP "127.0.0.1"
#define PORT 3000
int sockfd;


int main() {



    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP);
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(sockfd);
        return EXIT_FAILURE;
    }


    char *buff = "To jest wiadomosc od klienta\n";

    send(sockfd, buff, strlen(buff), 0);

    if(sendto(sockfd, (void *) buff, strlen(buff), 0, (struct sockaddr*)&server_addr, sizeof(server_addr) )){
        printf("hello message sent\n");
    }
    


    close(sockfd);
    return 0;
}

