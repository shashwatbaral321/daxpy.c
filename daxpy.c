#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define N 1000

float a = 2.0;
float x[N], y[N];

// Initialize x and y vectors with some values
void initialize_vectors() {
    for (int i = 0; i < N; i++) {
        x[i] = i * 1.0;
        y[i] = i * 2.0;
    }
}

void *daxpy(void *arg) {
    int thread_id = *(int *)arg;
    int start = (N / NUM_THREADS) * thread_id;
    int end = start + (N / NUM_THREADS);
    for (int i = start; i < end; i++) {
        y[i] = a * x[i] + y[i];
    }
    return NULL;
}

int main() {
    initialize_vectors();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, daxpy, &thread_ids[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print part of the result for verification
    printf("Sample y values after daxpy operation:\n");
    for (int i = 0; i < 10; i++) {
        printf("y[%d] = %f\n", i, y[i]);
    }

    return 0;
}


