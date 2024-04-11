#define _XOPEN_SOURCE 700 // hacky approach, might be necessary sometimes to enable sig* functions
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int operating_mode = -1;
int mode_changes = 0;



void handler(int signo, siginfo_t *info, void *extra){
    printf("Received operating moge: %d from sender with PID: %d\n", info->si_int, info->si_pid);
    mode_changes++;
    operating_mode = info->si_int;
    kill(info->si_pid, SIGUSR1);
}

int main() {
    printf("Catcher PID: %d\n", getpid());
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;          
    sigemptyset(&act.sa_mask);    
    act.sa_sigaction = handler;   
       
    //handling
    sigaction(SIGUSR1, &act, NULL);      


    while(1) {
        if(operating_mode == 1){
            for(int i = 0; i < 100; i++)
            printf("%i ", i);    
            printf("\n");
            operating_mode = -1;
        }
        else if(operating_mode == 2){
            printf("So far status has changed %d times\n", mode_changes);
            operating_mode = -1;
        }
        else if(operating_mode == 3){
            printf("Operating mode = 3 => EXITING...\n");
            exit(0);
        }
        sleep(1);
    } 

    return 0;
}