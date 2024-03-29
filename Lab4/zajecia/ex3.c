#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int global_variable = 1;



int main(){

    int local_variable = 1;
    char *local_string = "To jest napis";

    pid_t child_pid = fork();

    char *local_string2 = "testteest";

    if (child_pid == 0){   
        global_variable = 10;
        local_variable = 10;
        local_string = "To jest zmieniony napis";
        exit(0);

    }else{
        sleep(1);
        wait(NULL);
        printf("global: %d\n", global_variable);
        printf("local: %d\n", local_variable);
        printf("%s\n", local_string);
        printf("%s\n", local_string2);
    }
    
    wait(NULL);

    return 0;
}