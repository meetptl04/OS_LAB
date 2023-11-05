#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// without wait function

// int main() {
//     pid_t p;

//     printf("before fork\n");

//     p = fork();

//     if (p == 0) 
//     {
//         printf("I am child having id %d\n", getpid());
//         printf("My parent's id is %d\n", getppid());
//     } 
//     else if (p>0)
//     {
//         printf("My child's id is %d\n", p);
//         printf("I am parent having id %d\n", getpid());
//     }
//     else // p<0
//     {
//         printf("ERROR");
//     }

//     printf("Common\n");

//     return 0;
// }

// OUTPUT

// before fork
// My child's id is 36863
// I am parent having id 36862
// Common
// I am child having id 36863
// My parent's id is 36862
// Common


// WITH WAIT FUNCTION

// int main() {
//     pid_t p;

//     printf("before fork\n");

//     p = fork();

//     if (p == 0) // CHILD PROCESS
//     {
//         printf("I am child having id %d\n", getpid());
//         printf("My parent's id is %d\n", getppid());
//     } 
//     else if (p>0) // PARENT PROCESS
//     {
//         wait(NULL); // IT 
//         printf("My child's id is %d\n", p);
//         printf("I am parent having id %d\n", getpid());
//     }
//     else // p<0
//     {
//         printf("ERROR");
//     }

//     printf("Common\n");

//     return 0;
// }


// ORPHAN PROCESS : A child process that remains running even after its parent process is terminated or completed without waiting for the child process execution is called an orphan.

// int main() {
//     pid_t p;

//     printf("before fork\n");

//     p = fork();

//     if (p == 0) // CHILD PROCESS
//     {
//         sleep(2); //  because of this --> parent process terminate first. therefore in p==0 parent's id will not match with actual parent id
//         printf("I am child having id %d\n", getpid());
//         printf("My parent's id is %d\n", getppid());
//     } 
//     else if (p>0) // PARENT PROCESS
//     {
//         // wait(NULL); // IT 
//         //sleep(2); //--> to see this process in ps command
//         printf("I am parent having id %d\n", getpid());
//         printf("My child's id is %d\n", p);
//     }
//     else // p<0
//     {
//         printf("ERROR");
//     }

//     printf("Common\n");

//     return 0;
// }

// ZOMBIE PROCESS : A Zombie is a process that has completed its task but still, it shows an entry in a process table.

// int main() {
//     pid_t p;

//     printf("before fork\n");

//     p = fork();

//     if (p == 0) // CHILD PROCESS
//     {
//         printf("I am child having id %d\n", getpid());
//         printf("My parent's id is %d\n", getppid());
//     } 
//     else if (p>0) // PARENT PROCESS
//     {
//         wait(NULL); // THIS MAKE SURE THAT CHILD PROCESS CHANGE IT'S STATE (EXECUTING TO TERMINATE) 
//         sleep(2); //--> to see this process in ps command
//         printf("I am parent having id %d\n", getpid());
//         printf("My child's id is %d\n", p);
//     }
//     else // p<0
//     {
//         printf("ERROR");
//     }

//     printf("Common\n");

//     return 0;
// }


// QUESTIONS 

// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <stdlib.h>

// int Sum(int array[], int size) {
//     int sum = 0;
//     for (int i = 0; i < size; i++) {
//         sum += array[i];
//     }
//     return sum;
// }

// double Average(int array[], int size) {
//     int sum = Sum(array, size);
//     return (double)sum / size;
// }

// int Max(int array[], int size) {
//     int max = array[0];
//     for (int i = 1; i < size; i++) {
//         if (array[i] > max) {
//             max = array[i];
//         }
//     }
//     return max;
// }

// int main() {
//     int n;
//     printf("Enter the size of array: ");
//     scanf("%d", &n);
//     int arr[n];
//     for (int i = 0; i < n; i++) {
//         scanf("%d", &arr[i]);
//     }

//     pid_t pid_sum, pid_avg, pid_max;
//     pid_sum = fork();

//     if (pid_sum == 0) {
//         int sum = Sum(arr, n);
//         printf("Child process (sum) - Sum: %d\n", sum);
//         exit(0);
//     } else if (pid_sum < 0) {
//         printf("Fork (sum) failed.\n");
//     } else {
//         wait(NULL);
//     }

//     pid_avg = fork();

//     if (pid_avg == 0) {
//         double avg = Average(arr, n);
//         printf("Child process (average) - Average: %.2f\n", avg);
//         exit(0);
//     } else if (pid_avg < 0) {
//         printf("Fork (average) failed.\n");
//     } else {
//         wait(NULL);
//     }

//     pid_max = fork();

//     if (pid_max == 0) {
//         int max = Max(arr, n);
//         printf("Child process (max) - Maximum: %d\n", max);
//         exit(0);
//     } else if (pid_max < 0) {
//         printf("Fork (max) failed.\n");
//     } else {
//         wait(NULL);
//     }

//     printf("All the processes have completed.\n");

//     return 0;
// }
