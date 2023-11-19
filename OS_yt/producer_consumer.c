#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include <time.h>
int buffer[10];
sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mutex;
int count=0;
void* producer(){
    while(1){
        int x=rand()%100;
        sleep(1);
        //adding to the buffer
        sem_wait(&semEmpty); // wait while empty is not > 0 or decrease empty
        pthread_mutex_lock(&mutex);
        buffer[count]=x;
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&semFull); // increase full or wait if full is full
    }
}
void* consumer(){
    while(1){
        int y;
        sem_wait(&semFull);
        pthread_mutex_lock(&mutex);
        y=buffer[count-1];
        count--;
        pthread_mutex_unlock(&mutex);
        sem_post(&semEmpty);

        printf("GOT %d\n",y);
        sleep(1);
    }
}
int main(){
    srand(time(NULL));
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_t t1, t2;
    if(pthread_create(&t1, NULL, &producer, NULL)!=0){
        perror("Thread not created\n");
    }
    if(pthread_create(&t2, NULL, &consumer, NULL)!=0){
        perror("Thread not created\n");
    }
    if(pthread_join(t1, NULL)!=0){
        perror("Failed to join\n");
        }
    if(pthread_join(t2, NULL)!=0){
        perror("Failed to join\n");
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutex);
    return 0;
}