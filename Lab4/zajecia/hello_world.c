#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc,char *argv[]){



    printf("Hello world %d\n",getpid());

    return 0;
}