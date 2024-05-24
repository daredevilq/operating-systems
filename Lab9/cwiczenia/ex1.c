#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

void* thread_function(void* arg) {
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
    // First message
    printf("Hello world ; Thread ID: %ld - Message 1\n", pthread_self());

    pthread_testcancel();

    // Second message
    printf("Hello world ; Thread ID: %ld - Message 2\n", pthread_self());

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide the number of threads as an argument.\n");
        return 1;
    }

    long threads_number = strtol(argv[1], NULL, 10);

    pthread_t *threads = malloc(threads_number * sizeof(pthread_t));


    for (long i = 0; i < threads_number; i++) {
        int thread_id = pthread_create(&threads[i], NULL, thread_function, NULL);
        if (thread_id != 0) {
            fprintf(stderr, "failed to create thread %ld\n", i);
        }
    }

    //czekamy na zakonczenie watkow
    sleep(1); 

    for (long i = 0; i < threads_number; i++) {
        pthread_cancel(threads[i]);
    }

    for (long i = 0; i < threads_number; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return 0;
}
