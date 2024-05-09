#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

void signal_handler(int sig, siginfo_t *info, void *extra) {
    printf("dostarczony sygnal: %d\n", sig);
    printf("wartosc przeslana: %d\n", info->si_value.sival_int);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Not a suitable number of program parameters\n");
        return 1;
    }

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = signal_handler;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGUSR1);
    sigaddset(&action.sa_mask, SIGUSR2);

    int child = fork();
    if (child == 0) {
        sleep(1);
        printf("PID potomka: %d\n", getpid());
        sigaction(SIGUSR1, &action, NULL);
        sigaction(SIGUSR2, &action, NULL);
        exit(0);
    } else {
        int signal_number = atoi(argv[2]);
        union sigval val;
        val.sival_int = atoi(argv[1]);
        sigqueue(child, signal_number, val);

        int status;
        pid_t result = waitpid(child, &status, 0);
        if (result == -1) {
            perror("waitpid");
            exit(1);
        } else if (WIFEXITED(status)) {
            printf("Proces potomny zakonczony z kodem wyjscia: %d\n", WEXITSTATUS(status));
        } else {
            printf("Proces potomny zostal przerwany\n");
        }
    }

    return 0;
}
