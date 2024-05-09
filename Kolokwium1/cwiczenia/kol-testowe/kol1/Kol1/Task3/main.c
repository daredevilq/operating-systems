#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

int main() {
    pid_t pid;
    time_t t;
    int status;

    if ((pid = fork()) < 0)
        perror("fork");
    else if (pid == 0) {
        sleep(5);
        exit(5);
    }
    else {
        do {
            // Sprawdź status procesu potomka bez zawieszania procesu macierzystego
            if (waitpid(pid, &status, WNOHANG) == 0) {
                // Proces potomny nadal pracuje
                time(&t);
                printf("Proces potomny nadal pracuje %s", ctime(&t));
                sleep(1); // Uśpij proces macierzysty na jedną sekundę
            }
        } while (waitpid(pid, &status, WNOHANG) == 0); // Sprawdzaj, czy proces potomny się zakończył

        // Proces potomny zakończył się
        if (WIFEXITED(status))
            printf("Proces potomny zakończył się statusem %d\n", WEXITSTATUS(status));
        else
            puts("Proces potomny nie zakończył się prawidłowo");
    }

    puts("KONIEC");
    return 0;
}
