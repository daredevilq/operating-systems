#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>


int i = 0;
int fd[2];
int counter = 0;
int MAX_INT = 2147483647;
void handler(){
    write(fd[1], &i, sizeof(int));
    i++;
    //printf("handler %d\n",i);
}


void main_hanlder(){
    if(counter % 2 == 0){
        printf("Stopping main process %d\n", counter);
        // signal(SIGINT, main_hanlder);
        // sleep(MAX_INT);
    }
    else{
        printf("Starting main process %d\n", counter);
        // signal(SIGINT, main_hanlder);
        // sleep(0);
    }
    counter++;
}

int main(){
    pid_t child_1;
    pid_t child_2;
    pipe(fd);
    child_1 = fork();

    if (child_1 == 0)
    {   
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        sigprocmask(SIG_SETMASK, &set, NULL);
        
        close(fd[0]);
        while(1){
            signal(SIGUSR1, handler);
            sleep(1);
        }
    }else{
        child_2 = fork();

        if (child_2 == 0)
        {   
            sigset_t set2;
            sigemptyset(&set2);
            sigaddset(&set2, SIGINT);
            sigprocmask(SIG_SETMASK, &set2, NULL);
        
            int get_i;
            close(fd[1]);            
            while(1){
                if (read(fd[0], &get_i, sizeof(int)) != -1)
                {
                    printf("%d\n",get_i);
                    //printf("tutaj!\n");
                }
                
                sleep(1);
            }
        }
        else{
            close(fd[0]);
            close(fd[1]);  
            signal(SIGINT, main_hanlder);
            while (1)
            {
                if (counter % 2 == 0)
                {
                    kill(child_1, SIGUSR1);
                    sleep(1);
                }
                else{
                    printf("waiting\n");
                    sleep(1);
                }
                
            }

        }
        
    }
    




    return 0;
}