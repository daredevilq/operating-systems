#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;


    pipe(pipefd);
    pid = fork();

    if (pid == 0) { // Proces potomny
        // Zamykanie końcówki czytającej
        close(pipefd[0]);
        // Przekierowanie standardowego wyjścia do końcówki piszącej potoku
        dup2(pipefd[1], STDOUT_FILENO);

        // Uruchomienie polecenia "ps aux"
        execlp("ps", "ps", "aux", NULL);

    } else { // Proces rodzicielski
        // Zamykanie końcówki piszącej
        close(pipefd[1]);
        // Przekierowanie standardowego wejścia do końcówki czytającej potoku
        dup2(pipefd[0], STDIN_FILENO);
        // Uruchomienie polecenia "wc -l"
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
