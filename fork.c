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

int main() {
    pid_t p;

    printf("before fork\n");

    p = fork();

    if (p == 0) // CHILD PROCESS
    {
        printf("I am child having id %d\n", getpid());
        printf("My parent's id is %d\n", getppid());
    } 
    else if (p>0) // PARENT PROCESS
    {
        wait(NULL); // THIS MAKE SURE THAT CHILD PROCESS CHANGE IT'S STATE (EXECUTING TO TERMINATE) 
        sleep(2); //--> to see this process in ps command
        printf("I am parent having id %d\n", getpid());
        printf("My child's id is %d\n", p);
    }
    else // p<0
    {
        printf("ERROR");
    }

    printf("Common\n");

    return 0;
}