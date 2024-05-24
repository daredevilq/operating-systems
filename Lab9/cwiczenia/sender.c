#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    if(argc < 2){
        return EXIT_FAILURE;
    }

    long thread = strtol(argv[1], NULL, 10);

    

    return 0;
}