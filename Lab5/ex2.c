#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int counter = 0;
int sent = 0;
void handler(){
    counter++;
    printf("Counter %d\n", counter);
    printf("\n");
}



int main(){
    pid_t child_pid = fork();
    if (child_pid == 0){
        signal(SIGUSR1, handler);   
        printf("child pid %d\n", getpid());
        while(1){
            
        }
    
    }else{
        printf("parent pid %d\n", getpid());
        printf("child pid %d\n", child_pid);
        printf("\n");
        sleep(1);
        while (1){
            sent++;
            printf("Sent: %d\n", sent);
            kill(child_pid, SIGUSR1);
            sleep(1);
        }
    }
    

    return 0;
}