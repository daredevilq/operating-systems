#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fifo_path> <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* fifo_path = argv[1];
    int buf_size = atoi(argv[2]);

    if (buf_size <= 0) {
        fprintf(stderr, "error mienprwidlowa wielkosc buff\n");
        return EXIT_FAILURE;
    }

    char* buf = malloc(buf_size);
    if (!buf) {
        perror("error");
        return EXIT_FAILURE;
    }

    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("error");
        free(buf);
        return EXIT_FAILURE;
    }

    printf("Reader ready to read from FIFO.\n");

    int bytes_read;
    while ((bytes_read = read(fd, buf, buf_size)) > 0) {
        buf[bytes_read] = '\0';
        printf("Received: %s\n", buf);
    }

    if (bytes_read == -1) {
        perror("error");
    }

    printf("No more data. Exiting.\n");

    close(fd);
    free(buf);
    return EXIT_SUCCESS;
}
