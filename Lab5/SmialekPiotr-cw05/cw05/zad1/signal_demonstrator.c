#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <string.h>


void signal_hanlder(){
    printf("SIG_USR1 has been handeled!\n");
}


int main(int argc, char *argv[]){

    if (argc != 2){   
        printf("Wrong number of parameters\n");
        return 1;
    }



    if(strcmp(argv[1], "ignore") == 0){
        signal(SIGUSR1, SIG_IGN);
        raise(SIGUSR1);
    }
    else if(strcmp(argv[1], "handler") == 0){
        signal(SIGUSR1, signal_hanlder);
        raise(SIGUSR1);
    }
    else if(strcmp(argv[1], "mask") == 0){
        sigset_t new_signal_set;
        sigset_t blocked_signal_set;

        sigemptyset(&new_signal_set);
        sigaddset(&new_signal_set, SIGUSR1);
        sigprocmask(SIG_BLOCK, &new_signal_set, NULL);
        raise(SIGUSR1);

        sigpending(&blocked_signal_set);

        if (sigismember(&blocked_signal_set, SIGUSR1))
        {
            printf("Signal SIGUSR1 was blocked!\n");
        }else{
            printf("Something went wrong! Signal SIGUSR1 was NOT blocked!\n");
        }
        

    }
    else if (strcmp(argv[1], "none") == 0){
        signal(SIGUSR1, SIG_DFL);
        raise(SIGUSR1);
    }


    return 0;
}