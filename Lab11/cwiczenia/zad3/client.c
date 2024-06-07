#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char *message;

    if(argc != 2){
        perror("input required!\n");
        return EXIT_FAILURE;
    }


    message = argv[1];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    if (write(client_socket, message, strlen(message)) == -1) {
        perror("write");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Wysłano wiadomość: %s\n", message);

    close(client_socket);

    return 0;
}
