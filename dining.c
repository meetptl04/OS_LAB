#include <pthread.h>

#include <stdio.h>

#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
int state[N];
int phil[N] = { 0,1,2,3,4 };

int hunger[N] = { 2,3,1,4,5 };

pthread_mutex_t mutex;
pthread_cond_t cond[N];
void test(int phnum) {
    if (state[phnum] == HUNGRY &&
        state[(phnum + 1) % N] != EATING &&
        state[(phnum + N - 1) % N] != EATING &&
        hunger[phnum] >= hunger[(phnum + 1) % N] && hunger[phnum] >=
        hunger[(phnum + N - 1) % N]) {
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n",
            phnum + 1, (phnum + N - 1) % N + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        pthread_cond_signal( & cond[phnum]);
    }
}
void take_fork(int phnum) {
    pthread_mutex_lock( & mutex);
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    if (state[phnum] != EATING) {
        pthread_cond_wait( & cond[phnum], & mutex);
    }
    pthread_mutex_unlock( & mutex);
    sleep(1);
}
void put_fork(int phnum) {
    pthread_mutex_lock( & mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",
        phnum + 1, (phnum + N - 1) % N + 1, phnum + 1);
    hunger[phnum] = hunger[phnum] - 1;
    test((phnum + 1) % N);
    test((phnum + N - 1) % N);
    pthread_mutex_unlock( & mutex);
}
void * philosopher(void * num) {
    while (1) {
        int * i = num;
        sleep(1);
        take_fork( * i);
        sleep(0);
        put_fork( * i);
        
    }
}
int main() {
    int i;
    pthread_t thread_id[N];
    pthread_mutex_init( & mutex, NULL);
    for (i = 0; i < N; i++) {
        pthread_cond_init( & cond[i], NULL);
    }
    for (i = 0; i < N; i++) {
        pthread_create( & thread_id[i], NULL, philosopher, & phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}