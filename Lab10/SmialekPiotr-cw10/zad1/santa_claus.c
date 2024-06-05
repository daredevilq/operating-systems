#include <pthread.h>    
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// najpierw zadjecia 1 -> strimingowe potem zajeia 2 -> datagramowe

#define NUMBER_OF_REINDEERS 9
#define PRESENTS_TO_DELIVER 4

pthread_mutex_t santa_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t santa_cond = PTHREAD_COND_INITIALIZER;

int presents_delivered = 0;
int waiting_reindeers = 0;

pthread_t santa_thread;
pthread_t renifery_threads[NUMBER_OF_REINDEERS];

pthread_mutex_t reindeers_mutexes[9] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

int reindeers_back_count = 0;
pthread_mutex_t reindeers_back_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t santa_thread;
pthread_t reindeers_threads[9];

void *santa_handler(void * arg){
  // cycle 4 times to deliver toys
    for (int i = 0; i < 4; i++) {
        // wait for reindeers to wake up santa
        pthread_cond_wait(&santa_cond, &santa_mutex);
        printf("Mikołaj: budzę się\n");

        printf("Mikołaj: dostarczam zabawki\n");
        // santa is delivering toys for 2-4 seconds
        sleep(rand() % 3 + 2);

        // release all reindeers
        for (int j = 0; j < 9; j++) {
            pthread_mutex_unlock(&reindeers_mutexes[j]);
        }

        printf("Mikołaj: zasypiam\n");
    }

    // cancel all reindeer threads
    for (int j = 0; j < 9; j++) {
        pthread_cancel(reindeers_threads[j]);
    }

    return NULL;
}

void *reindeers_handler(void * arg){
     // dereference argument pointer to get reindeer id
    int id = *(int*)arg;
    // set cancel type to asynchronous to be able to cancel thread immediately
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // lock reindeer mutex to prevent cycling until reindeers do not come back from santa claus - when santa releases their mutexes
    pthread_mutex_lock(&reindeers_mutexes[id]);
    while(1) {
        // reindeer is on vacation for 5-10 seconds
        sleep(rand() % 6 + 5);

        // lock counter mutex to increment counter of reindeers that has come back
        pthread_mutex_lock(&reindeers_back_mutex);
        printf("Renifer: czeka %d reniferów, %d\n", reindeers_back_count, id);

        // increment counter and check if all reindeers are back
        reindeers_back_count++;
        if (reindeers_back_count == 9) {
            printf("Renifer: budzę Mikołaja, %d\n", id);
            // if all reindeers are back, wake up santa and reset counter
            pthread_cond_signal(&santa_cond);
            reindeers_back_count = 0;
        }

        // unlock counter mutex
        pthread_mutex_unlock(&reindeers_back_mutex);

        // wait for santa to release reindeer mutex
        pthread_mutex_lock(&reindeers_mutexes[id]);

        // reindeer is flying on vacation
        printf("Renifer: lecę na wakacje, %d\n", id);
    }  

    return NULL;
}


int main(){

    pthread_create(&santa_thread, NULL, santa_handler, NULL);

    for (int i = 0; i < NUMBER_OF_REINDEERS; i++)
    {
        pthread_create(&renifery_threads[i], NULL, reindeers_handler, NULL);

    }


    for (int i = 0; i < NUMBER_OF_REINDEERS; i++)
    {
        pthread_join(renifery_threads[i], NULL);

    }

    pthread_join(santa_thread, NULL);


    return 0;
}