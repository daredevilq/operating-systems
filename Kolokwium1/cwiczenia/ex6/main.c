#define _XOPEN_SOURCE 700 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Proces potomny
        close(fd[1]); // Zamykamy końcówkę zapisu, ponieważ będziemy czytać z potoku
        dup2(fd[0], STDIN_FILENO); // Przekierowanie standardowego wejścia na potok


        execlp("grep", "grep", "Ala", NULL); // Uruchamiamy grep
        perror("execlp"); // Obsługa błędów, jeśli execlp zawiedzie
        exit(EXIT_FAILURE);
    } else { // Proces rodzicielski
        close(fd[0]); // Zamykamy końcówkę czytania, ponieważ będziemy pisać do potoku

        // Zawartość pliku, którą chcemy przekazać do grep
        char *buff = "file.txt";

        // Pisanie do potoku
        if (write(fd[1], buff, strlen(buff)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        
        close(fd[1]); // Po zakończeniu pisania zamykamy końcówkę zapisu
    }

    return 0;
}
