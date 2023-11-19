#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadFunction(void* arg) {
    int threadId = *(int*)arg;

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex);

        // Critical section
        printf("Thread %d entered the critical section.\n", threadId + 1);
        // Perform critical section operations

        pthread_mutex_unlock(&mutex);

        // Remainder section
        // Perform other operations
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[2];
    int threadIds[2] = {0, 1};

    for (int i = 0; i < 2; ++i) {
        if(pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if(pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            return 2;
        }
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
