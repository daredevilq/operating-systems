#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int status = 0;    
    pid_t child_pid, wpid;

    if (argc != 2){
        printf("Wrong input, one int >0 type required\n");
        return 1;
    }
    char* endptr;
    int no_processes = strtol(argv[1], &endptr,10);

    if (no_processes <= 0){
        printf("Input argument shoud be >0\n");
    }
    
    for (int i = 0; i < no_processes; i++)
    {
        child_pid = fork();

        if (child_pid == 0)
        {
            printf("%d Child process: PID: %d PPID: %d\n", i, getpid(),getppid());
            exit(0);
        }
        
    }
    //waiting for all children processes
    while ((wpid = wait(&status)) > 0);

    printf("Number of created processes: %d\n", no_processes);
    
    return 0;
}