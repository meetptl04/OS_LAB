
// Peterson's algorithm (Critical Section Problem)

// #include<stdio.h>
// #include <stdbool.h>

// int turn;
// bool flag[2]={true};

// do{
//     flag[i]=true;
//     turn=j;
//     while(turn==j && flag[j]==true);
//     // critical section
//     flag[i]=false;
//     // remainder section
// }while(true);

// do{
//     flag[j]=true;
//     turn=i;
//     while(turn==i && flag[i]==true);
//     // critical section
//     flag[j]=false;
//     // remainder section
// // }while(true);



#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

int turn;
bool flag[2] = {false};

void lock(int i) {
    int j = 1 - i; // Index of the other thread

    flag[i] = true;
    turn = i;

    while (turn == i && flag[j] == true) {
        // Wait for the other thread to finish
        // This is the busy-waiting part for Peterson's algorithm
    }
}

void unlock(int i) {
    flag[i] = false;
}

void* threadFunction(void* arg) {
    int threadId = *(int*)arg;

    for (int i = 0; i < 5; ++i) {
        lock(threadId);

        // Critical section
        printf("Thread %d entered the critical section.\n", threadId + 1);
        // Perform critical section operations

        unlock(threadId);

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

    return 0;
}

