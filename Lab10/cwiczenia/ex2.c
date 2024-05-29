#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int global_variable = 0;

pthread_mutexattr_t attr;


pthread_mutex_t mutex;
    


void *hello( void * arg){
    pthread_mutex_lock(&mutex);
    while (1)
    {
    global_variable++;
    printf("Global variable incremented to %d, thread %ld\n", global_variable, pthread_self());        
    }
    pthread_mutex_unlock(&mutex);

}



int main(int argc, char *argv[]){


    pthread_mutexattr_init(&attr);

    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    
    pthread_mutex_init(&mutex, &attr);

    int no_threads = atoi(argv[1]);

    pthread_t threads[no_threads];

    for (int i = 0; i < no_threads; i++)
    {
        pthread_create(&threads[i], NULL, hello, NULL);
    }
    

    
    for (int i = 0; i < no_threads; i++)
    {   
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);


    return 0;
}