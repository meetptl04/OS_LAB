#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define N 5
int number[N] = {0};
bool choosing[N] = {false};


void lock(int i) {
    choosing[i] = true;
    int max = 0;

    for (int k = 0; k < N; ++k) {
        if (number[k] > max) {
            max = number[k];
        }
    }

    number[i] = 1 + max;
    // printf("Number value : %d\n",number[i]);
    choosing[i] = false;

    for (int j = 0; j < N; ++j) {
        if (j != i) {
            while (choosing[j]);
            while (number[j] != 0 && (number[j] < number[i] || (number[j] == number[i] && j < i)));
        }
    }
}


void unlock(int i) {
    choosing[i] = false;
    number[i] = 0;
}

void* threadFunction(void* args) {
    int threadId = *(int*)args;

    for (int i = 0; i < 1; i++) {
        lock(threadId);

        // Critical Section
        // printf("Number : %d\n",number[i]);
        printf("Thread %d entered the critical section.\n", threadId + 1);

        unlock(threadId);

        // Remainder section
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    int threadIds[N] = {0, 1, 2, 3, 4};

    for (int i = 0; i < N; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]) != 0) {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            return 2;
        }
    }
    return 0;
}
