#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(){

    pid_t child_pid = fork();

    if (child_pid != 0)
    {
        waitpid(child_pid, NULL, 0);

        printf("this is parent\n");
    }else{

        char* const av[] = {"ls", "-al", NULL};

        //execlp("ls", "-al", NULL);
        //execl("/bin/ls", "ls", "-al", NULL);
        
        execv("/bin/ls", av);
        
        exit(0);
    }
    

    
    return 0;
}