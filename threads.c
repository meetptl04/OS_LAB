#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h> // used for sleep function
#include<unistd.h>


// Syntax of creating thread.

// int pthread_create(pthread_t * thread,const pthread_attr_t * attr,void * (*start_routine)(void *),void *arg);

// pthread_exit: used to terminate a thread
// Syntax:

// void pthread_exit(void *retval);

// pthread_join: used to wait for the termination of a thread.
// Syntax:

// int pthread_join(pthread_t th,void **thread_return);

// void *my_thread(void *arg) {
//   int i;
//   for (i = 0; i < 10; i++) {
//     printf("Hello from thread! : %d \n",i);
//     sleep(1);
//   }
//   return NULL;
// }

// int main() {
//   pthread_t thread;
//   int i;

//   pthread_create(&thread, NULL, my_thread, NULL);

//   for (i = 0; i < 10; i++) {
//     printf("Hello from main! : %d \n",i);
//     sleep(1);
//   }

//   pthread_join(thread, NULL);

//   return 0;
// }

// OUTPUT : 

// Hello from main! : 0 
// Hello from thread! : 0 
// Hello from main! : 1 
// Hello from thread! : 1 
// Hello from main! : 2 
// Hello from thread! : 2 
// Hello from main! : 3 
// Hello from thread! : 3 
// Hello from main! : 4 
// Hello from thread! : 4 
// Hello from main! : 5 
// Hello from thread! : 5 
// Hello from main! : 6 
// Hello from thread! : 6 
// Hello from main! : 7 
// Hello from thread! : 7 
// Hello from main! : 8 
// Hello from thread! : 8 
// Hello from main! : 9 
// Hello from thread! : 9 


void *func(void *var)
{
    sleep(2);
    printf("We are using thread")  ;
    return NULL;
}

int main()
{
    pthread_t t_id;
    printf("Before using threading");
    ptherad_creat(&t_id,NULL,func,NULL);
    pthread_join(t_id,NULL);

    printf("After Thread \n");

    exit(0);
}