#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int global_variable = 0;

pthread_mutexattr_t attr;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *hello(void *arg) {
    pthread_mutex_lock(&mutex);
    while (1) {   
        while (global_variable < 5) {
            pthread_cond_wait(&cond, &mutex);
        }
        global_variable++;
        printf("HELLO, thread %ld\n", pthread_self());
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
}

int main(int argc, char *argv[]) {

    int no_threads = atoi(argv[1]);


    pthread_t threads[no_threads];

    for (int i = 0; i < no_threads; i++) {
        if (pthread_create(&threads[i], NULL, hello, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 5; i++) {
        sleep(1);
        pthread_mutex_lock(&mutex);
        global_variable++;
        printf("Main thread incrementing global_variable to %d\n", global_variable);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    for (int i = 0; i < no_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
