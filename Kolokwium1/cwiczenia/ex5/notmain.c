#define _XOPEN_SOURCE 700 // hacky approach, might be necessary sometimes to enable sig* functions

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>





void SIGUSR1_action(int signo, siginfo_t *info, void *extra){
    /* Retrieve information from signal info structure */
    int int_val = info->si_value.sival_int;
    printf("Received status: %d from pid: %d\n",int_val, info->si_pid);
    printf("%d\n", signo);
    printf("%d\n", info->si_code);
    printf("%d\n", info->si_code);
    printf("%d\n", info->si_signo);

}

int main() {
    /* Print out current catcher's PID*/
    printf("Catcher PID: %d\n", getpid());


    struct sigaction action;
    action.sa_sigaction = SIGUSR1_action;   // register callback
    action.sa_flags = SA_SIGINFO;           // set flag to SIGINFO so handler will be called with all 3 arguments
    sigemptyset(&action.sa_mask);           // clear all signal masks during handler

    sigaction(SIGUSR1, &action, NULL);      // proper registration of the signal action

   while(1)
    sleep(1);

    return 0;
}