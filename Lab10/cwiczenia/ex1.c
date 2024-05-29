#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int global_variable = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    


void *hello( void * arg){

    pthread_mutex_lock(&mutex);
    global_variable++;
    printf("Global variable incremented to %d, thread %ld\n", global_variable, pthread_self());
    pthread_mutex_unlock(&mutex);

}



int main(int argc, char *argv[]){


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


    return 0;
}