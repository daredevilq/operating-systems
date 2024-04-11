#define _XOPEN_SOURCE 700 // hacky approach, might be necessary sometimes to enable sig* functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int signo) {
    printf("Confirmation received\n");
}


int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Wrong input!\n");
        return EXIT_FAILURE;
    }

    printf("Sender PID: %d\n", getpid());

    signal(SIGUSR1, handler);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGINT);

    pid_t catcher_pid = strtol(argv[1], NULL, 10);
    long operating_mode = strtol(argv[2], NULL, 10);

    union sigval value = {operating_mode};

    sigqueue(catcher_pid, SIGUSR1, value);
    printf("Signal sent to process PID: %d with operationg mode number %ld\n", catcher_pid, operating_mode);

    sigsuspend(&mask);
    return 0;
}