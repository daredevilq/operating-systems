#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fifo_path> <message>\n", argv[0]);
        return 1;
    }

    const char *fifo_path = argv[1];
    const char *message = argv[2];

    if (mkfifo(fifo_path, 0666) == -1) { // handloweanie bledow
        if (errno != EEXIST) {
            perror("mkfifo");
            return 1;
        }
    }

    int fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}
