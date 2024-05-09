#define _XOPEN_SOURCE 700 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>



int main(int argc, char **argv) {


        long pid = strtol(argv[1], NULL, 10);
        
        char word[] = "some word";
        printf("parent\n");
        union sigval value;
        value.sival_int = 100;
        //value.sival_ptr = (void*)word; // Przekazanie wskaźnika na łańcuch znaków

        // Wysłanie sygnału SIGUSR1 do potomka z dodatkowymi danymi
        sigqueue(pid, SIGUSR1, value);

        while (1)
            sleep(1);


    return 0;
}
