#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>




void* thread_function(void* arg) {
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    printf("Hello world ; Thread ID: %ld - Message 1\n", pthread_self());

}

int main(int argc, char *argv[]){

    pthread_t *thread  = malloc(sizeof(pthread_t));

    pthread_create(&thread, NULL, thread_function, NULL);



    return 0;
}