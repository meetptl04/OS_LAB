#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
sem_t semaphore;
void* login(void* args){
    printf("%d Waiting in the login queue\n", *(int*)args);
    sem_wait(&semaphore);
    printf("%d logged in\n",*(int*)args);
    sleep(rand()%5+1);
    printf("%d logged out\n",*(int*)args);
    sem_post(&semaphore);
}
int main(){
    sem_init(&semaphore, 0, 12);
    pthread_t th[20];
    for(int i=0;i<20;i++){
        int* a=malloc(sizeof(int));
        *a=i;
        if(pthread_create(&th[i],NULL,&login,a)!=0){
            perror("Failed to create thread\n");
        }
    }
    for(int i=0;i<20;i++){
        if(pthread_join(th[i],NULL)!=0){
            perror("Thread failed to join\n");
        }
    }
    sem_destroy(&semaphore);
    return 0;
}