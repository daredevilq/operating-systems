#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc != 4){
        printf("Not a suitable number of program parameters\n");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) { //blad
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        char *args[] = {"./calc", argv[1], argv[2], argv[3], NULL};
        execvp("./calc", args);
        perror("execvp");
        exit(1);
    } else {
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("proces potomny zatrzymany ze statusem: %d\n", WEXITSTATUS(status));
        } else {
            printf("proces potomny zatrzymany\n");
        }
    }

    return 0;
}
