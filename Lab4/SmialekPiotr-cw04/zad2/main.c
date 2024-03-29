#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int global_variable = 7;



int main(int argc, char *argv[]){

    if (argc != 2){   
        printf("Wrong input!\n");
        return 1;
    }
        
    printf("Program name: %s\n", argv[0]);

    int local_variable = 7;

    pid_t child_pid = fork();

    if (child_pid == 0){
        
        printf("Child process\n");
        global_variable++;
        local_variable++;

        printf("Child pid = %d, parent pid: %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local_variable, global_variable);
        printf("------------------\n");
        printf("execl() program:\n");
        int status_child = execl("/bin/ls", "ls", "-l", argv[1], NULL);
        printf("------------------\n");
        exit(status_child);
    }
    
    int status_parent = 0;

    wait(&status_parent);

    //returns status of wait
    int child_status_returned = WEXITSTATUS(status_parent);

    printf("Parent process\n");
    printf("parent pid = %d, child pid = %d \n", getpid(), child_pid);
    printf("Child exit code: %d \n", child_status_returned);
    printf("parent's local = %d, parent's global = %d \n", local_variable, global_variable);

    return child_status_returned;
}