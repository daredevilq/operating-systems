#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main() {
    int fd[2];
    int fd2[2];

    pipe(fd);
    pipe(fd2);

    char* napis = "Hello world!\0";
    pid_t child_pid = fork();
    if (child_pid == 0) { 
        //close(fd[1]);
        close(fd2[0]);
        
        char napis_child[100]; 
        ssize_t bytes_read = read(fd[0], napis_child, sizeof(napis_child)); // Odbieranie danych
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        napis_child[0] = 'A';
        
        ssize_t bytes_written_child = write(fd[1], napis_child, strlen(napis_child));
        //napis_child[bytes_read] = '\0'; 
        //printf("%s\n", napis_child);
    } else { 
        //close(fd[0]);
        close(fd2[1]);

        ssize_t bytes_written = write(fd[1], napis, strlen(napis)); 
        // if (bytes_written == -1) {
        //     perror("write");
        //     exit(EXIT_FAILURE);
        // }

        char napis_parent[100]; 
        char napis_parent_2[100];
        ssize_t bytes_read_parent = read(fd[0], napis_parent, sizeof(napis_parent)); // Odbieranie danych
        if (bytes_read_parent == -1) {
            perror("read"); 
            exit(EXIT_FAILURE);
        }
        printf("%s\n", napis_parent);

        ssize_t bytes_read_parent2 = read(fd[0], napis_parent_2, sizeof(napis_parent_2)); // Odbieranie danych
        if (bytes_read_parent2 == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", napis_parent_2);

    }
    return 0;
}