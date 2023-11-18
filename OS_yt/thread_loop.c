#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write mails
    }
}

int main(/*int argc, char* argv[]*/) {
    pthread_t th[4];
    pthread_mutex_init(&mutex,NULL);
    for (int i=0;i<4;i++){
        if(pthread_create(&th[i],NULL,&routine,NULL) != 0){
            perror("Failed to create thread!");
            return 1;
        }
        printf("Thread %d is started\n",i);
        // if (pthread_join(th[i],NULL) != 0){
        //     return 2;
        // }
        // printf("Thread %d is finished execution\n",i);

    }
    for (int i=0;i<4;i++){
        if (pthread_join(th[i],NULL) != 0){
            return 2;
        }
        printf("Thread %d is finished execution\n",i);
    }
    // if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
    //     return 1;
    // }
    // if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
    //     return 2;
    // }
    // if (pthread_join(p1, NULL) != 0) {
    //     return 3;
    // }
    // if (pthread_join(p2, NULL) != 0) {
    //     return 4;
    // }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}