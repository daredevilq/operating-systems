#include <pthread.h>    
#include <stdio.h>
#include <unistd.h>
// najpierw zadjecia 1 -> strimingowe potem zajeia 2 -> datagramowe

#define NUMBER_OF_REINDEERS 9
#define PRESENTS_TO_DELIVER 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int presents_delivered = 0;
int waiting_reindeers = 0;


void *santa_handler(void * arg){
    pthread_mutex_lock(&mutex);

    while(waiting_reindeers != NUMBER_OF_REINDEERS){
        printf("Santa is sleeping ... \n");
        sleep(1);
        pthread_cond_wait(&cond, &mutex);
    }



    pthread_mutex_unlock(&mutex);

}

void *reindeers_handler(void * arg){

}


int main(){


    pthread_t santa_thread;
    pthread_t renifery_threads[NUMBER_OF_REINDEERS];

    pthread_create(&santa_thread, NULL, santa_handler, NULL);

    for (int i = 0; i < NUMBER_OF_REINDEERS; i++)
    {
        pthread_create(&renifery_threads[i], NULL, reindeers_handler, NULL);

    }
    


    for (int i = 0; i < NUMBER_OF_REINDEERS; i++)
    {
        pthread_join(renifery_threads[i], NULL);

    }
    




    return 0;
}