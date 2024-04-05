#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


void handler(){
    printf("DOSTALEM SYGNAL!!!\n");
}

int main(){

    pid_t child_pid = fork();

    if (child_pid == 0)
    {   
        sigset_t mask;
        sigemptyset(&mask);
        sigfillset(&mask);  
        // printf(""przeeed mas)
        sigprocmask(SIG_SETMASK, &mask, NULL);
        
        while(1);

    }else{
        sleep(2);
        kill(child_pid, SIGINT);
        // kill(child_pid,)
    }
    

    return 0;
}