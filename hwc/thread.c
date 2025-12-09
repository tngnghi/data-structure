#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define ITERATIONS_PER_THREAD 100000

long long shared_counter = 0;

pthread_mutex_t counter_mutex;

void *increment_counter(void *threadid) {
    long tid = (long)threadid;
    int i;
    
    for (i = 0; i < ITERATIONS_PER_THREAD; i++) {
        pthread_mutex_lock(&counter_mutex);
        
        shared_counter++;
        
        pthread_mutex_unlock(&counter_mutex);
        
    }

    printf("Thread %ld finished. Local iterations: %d\n", tid, ITERATIONS_PER_THREAD);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    long long expected_total = (long long)NUM_THREADS * ITERATIONS_PER_THREAD;

    if (pthread_mutex_init(&counter_mutex, NULL) != 0) {
        printf("\nMutex initialization failed\n");
        return 1;
    }

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        
        if (rc) {
            fprintf(stderr, "Error: pthread_create failed, return code: %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    pthread_mutex_destroy(&counter_mutex);

    printf("\nAll threads finished.\n");
    printf("Expected total: %lld\n", expected_total);
    printf("Actual shared_counter value: %lld\n", shared_counter);

    if (shared_counter == expected_total) {
        printf("Result is correct. Mutex synchronization successful!\n");
    } else {
        printf("Result is INCORRECT. Data corruption occurred! (This should not happen with proper mutex use)\n");
    }

    return 0;
}