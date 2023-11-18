#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>


void* dice(){
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    //printf("%d\n",value);
    printf("Thread result : %p\n",result);
    return (void*) result;
}

int main(){
    int* res;
    srand(time(NULL));
    pthread_t th;
    if(pthread_create(&th,NULL,&dice,NULL) != 0){
        return 1;
    }
    if (pthread_join(th, (void**) &res) != 0){
        return 2;
    }
    printf("Main res : %p\n",res);
    printf("Return vlaue : %d\n",*res);
    free(res);
    return 0;
}