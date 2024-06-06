#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NUMBER_OF_REINDEERS 9
#define PRESENTS_TO_DELIVER 4

pthread_mutex_t santa_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t santa_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t reindeers_mutexes[NUMBER_OF_REINDEERS] = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER
};

int reindeers_back_count = 0;
pthread_mutex_t reindeers_back_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t santa_thread;
pthread_t reindeers_threads[NUMBER_OF_REINDEERS];

void *santa_handler(void *arg) {
    for (int i = 0; i < PRESENTS_TO_DELIVER; i++) {
        pthread_mutex_lock(&santa_mutex);
        pthread_cond_wait(&santa_cond, &santa_mutex);
        pthread_mutex_unlock(&santa_mutex);

        printf("Santa wakes up\n");

        printf("Santa delivers toys\n");
        sleep(rand() % 3 + 2);
        for (int j = 0; j < NUMBER_OF_REINDEERS; j++) {
            pthread_mutex_unlock(&reindeers_mutexes[j]);
        }

        printf("Santa falls asleep\n");
    }

    for (int j = 0; j < NUMBER_OF_REINDEERS; j++) {
        pthread_cancel(reindeers_threads[j]);
    }

    return NULL;
}

void *reindeers_handler(void *arg) {
    int id = *(int *)arg;
    free(arg);

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    pthread_mutex_lock(&reindeers_mutexes[id]);
    while (1) {
        sleep(rand() % 6 + 5);

        pthread_mutex_lock(&reindeers_back_mutex);
        reindeers_back_count++;
        printf("Reindeer %d: waiting, %d reindeers back\n", id, reindeers_back_count);
        if (reindeers_back_count == NUMBER_OF_REINDEERS) {
            printf("Reindeer %d: waking up Santa\n", id);
            pthread_mutex_lock(&santa_mutex);
            pthread_cond_signal(&santa_cond);
            pthread_mutex_unlock(&santa_mutex);
            reindeers_back_count = 0;
        }
        pthread_mutex_unlock(&reindeers_back_mutex);

        pthread_mutex_lock(&reindeers_mutexes[id]);
        printf("Reindeer %d: going on vacation\n", id);
    }

    return NULL;
}

int main() {
    pthread_create(&santa_thread, NULL, santa_handler, NULL);

    for (int i = 0; i < NUMBER_OF_REINDEERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&reindeers_threads[i], NULL, reindeers_handler, id);
    }

    for (int i = 0; i < NUMBER_OF_REINDEERS; i++) {
        pthread_join(reindeers_threads[i], NULL);
    }

    pthread_join(santa_thread, NULL);

    return 0;
}
