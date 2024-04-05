#include <stdio.h>
#include <signal.h>
#include <time.h>


void handler(){
    printf("ALE SYGNAL!!!!!!!!!\n");
}



int main(){
    signal(SIGINT, handler);

    raise(SIGINT);


    return 0;
}