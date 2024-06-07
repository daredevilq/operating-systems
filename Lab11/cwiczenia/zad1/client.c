#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "./socket"

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    char *message = "HELO HELO HELO !!!!!!!!!!!!!!!!!!!";

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
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
