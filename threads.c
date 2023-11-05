#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h> // used for sleep function
#include<unistd.h>
#include<sys/wait.h>

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


// void *func(void *var)
// {
//     sleep(2);
//     printf("We are using thread\n")  ;
//     return NULL;
// }

// int main()
// {
//     pthread_t t_id;
//     printf("Before using threading\n");
//     pthread_create(&t_id,NULL,func,NULL);
//     pthread_join(t_id,NULL);

//     printf("After Thread \n");

//     exit(0);
// }

// Parallel Thread management using Pthreads library. Implement a data parallelism using multi-threading


// #define NUM_THREADS 4
// #define DATA_SIZE 100

// int data[DATA_SIZE];
// int result[DATA_SIZE];

// void* process_data(void* arg) {
//     int thread_id = *(int*)arg;
//     int chunk_size = DATA_SIZE / NUM_THREADS;
//     int start_index = thread_id * chunk_size;
//     int end_index = start_index + chunk_size;
    
//     for (int i = start_index; i < end_index; i++) {
//         // Perform the operation on the data element
//         result[i] = data[i] * 2;
        
//         // Print which thread is processing which number
//         printf("Thread %d: Result[%d] = %d\n", thread_id, i, result[i]);
//     }
    
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     int thread_ids[NUM_THREADS];
    
//     // Initialize data array
//     for (int i = 0; i < DATA_SIZE; i++) {
//         data[i] = i + 1;
//     }
    
//     // Create threads
//     for (int i = 0; i < NUM_THREADS; i++) {
//         thread_ids[i] = i;
//         pthread_create(&threads[i], NULL, process_data, &thread_ids[i]);
//     }
    
//     // Wait for threads to complete
//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }
    
//     return 0;
// }



// void* printEven(void* arg) {
//     for (int i = 2; i <= 10; i += 2) {
//         printf("Even Thread: %d\n", i);
//         usleep(100); // Add a small delay for demonstration purposes
//     }
//     pthread_exit(NULL);
// }

// void* printOdd(void* arg) {
//     for (int i = 1; i <= 9; i += 2) {
//         printf("Odd Thread: %d\n", i);
//         usleep(100); // Add a small delay for demonstration purposes
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t evenThread, oddThread;

//     pthread_create(&evenThread, NULL, printEven, NULL);
//     pthread_create(&oddThread, NULL, printOdd, NULL);

//     pthread_join(evenThread, NULL);
//     pthread_join(oddThread, NULL);

//     return 0;
// }




// Thread Synchronization



// #define NUM_THREADS 5

// int counter = 0;
// pthread_mutex_t mutex; // Declare a mutex variable mutex to control access to the counter

// void* increment_counter(void* thread_id) {
//     int tid = *((int*) thread_id);

//     // Acquire the lock
//     pthread_mutex_lock(&mutex);

//     printf("Thread %d: Counter before increment: %d\n", tid, counter);
//     counter++;
//     printf("Thread %d: Counter after increment: %d\n", tid, counter);

//     // Release the lock
//     pthread_mutex_unlock(&mutex);

//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     int thread_ids[NUM_THREADS];

//     // Initialize the mutex
//     pthread_mutex_init(&mutex, NULL);

//     // Create threads
//     for (int i = 0; i < NUM_THREADS; i++) {
//         thread_ids[i] = i;

//         if (pthread_create(&threads[i], NULL, increment_counter, (void*) &thread_ids[i])) {
//             fprintf(stderr, "Error creating thread\n");
//             return 1;
//         }
//     }

//     // Wait for threads to finish
//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     // Destroy the mutex
//     pthread_mutex_destroy(&mutex);

//     printf("Final counter value: %d\n", counter);

//     return 0;
// }



// #define NUM_THREADS 3
// #define PRINT_COUNT 3

// pthread_mutex_t mutex;
// pthread_cond_t cond[NUM_THREADS];
// int current_thread = 0;

// void *printLetter(void *letter) {
//     char letterToPrint = *(char *)letter;

//     for (int i = 0; i < PRINT_COUNT; i++) {
//         pthread_mutex_lock(&mutex);

//         while (letterToPrint - 'A' != current_thread) {
//             pthread_cond_wait(&cond[letterToPrint - 'A'], &mutex);
//         }

//         printf("%c", letterToPrint);
//         current_thread = (current_thread + 1) % NUM_THREADS;

//         pthread_cond_signal(&cond[current_thread]);
//         pthread_mutex_unlock(&mutex);
//     }

//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t threads[NUM_THREADS];
//     char letters[NUM_THREADS] = {'A', 'B', 'C'};

//     pthread_mutex_init(&mutex, NULL);

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_cond_init(&cond[i], NULL);
//     }

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_create(&threads[i], NULL, printLetter, &letters[i]);
//     }

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     pthread_mutex_destroy(&mutex);

//     for (int i = 0; i < NUM_THREADS; i++) {
//         pthread_cond_destroy(&cond[i]);
//     }

//     printf("\n");

//     return 0;
// }

pthread_mutex_t mutex;
pthread_cond_t cond;
int current = 1;

void *even() {
    for (int i = 2; i <= 10; i += 2) {
        pthread_mutex_lock(&mutex);
        while (current != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Even Thread: %d\n", i);
        current = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *odd() {
    for (int i = 1; i <= 9; i += 2) {
        pthread_mutex_lock(&mutex);
        while (current != 2) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Odd Thread: %d\n", i);
        current = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}