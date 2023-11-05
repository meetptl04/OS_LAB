// Non-pre-emptive Round robin
#include <stdio.h>

#include <stdbool.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int burstTimeRemaining;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool isComplete;
    bool inQueue;
};
void checkForNewArrivals(struct Process processes[],
    const int n,
        const int currentTime, int
    readyQueue[], int * queueSize) {
    for (int i = 0; i < n; i++) {
        struct Process p = processes[i];
        if (p.arrivalTime <= currentTime && !p.inQueue && !p.isComplete) {
            processes[i].inQueue = true;
            readyQueue[( * queueSize) ++] = i;
        }
    }
}
void updateQueue(struct Process processes[],
    const int n,
        const int quantum, int readyQueue[], int *
            queueSize, int * currentTime, int * programsExecuted) {
    int i = readyQueue[0];
    for (int j = 0; j < * queueSize - 1; j++)
        readyQueue[j] = readyQueue[j + 1];
    ( * queueSize) --;
    if (processes[i].burstTimeRemaining <= quantum) {
        processes[i].isComplete = true;
        ( * currentTime) += processes[i].burstTimeRemaining;
        processes[i].completionTime = ( * currentTime);
        processes[i].waitingTime = processes[i].completionTime - processes[i].arrivalTime - processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        if (processes[i].waitingTime < 0)
            processes[i].waitingTime = 0;
        processes[i].burstTimeRemaining = 0;
        if ( * programsExecuted != n) {
            checkForNewArrivals(processes, n, * currentTime, readyQueue, queueSize);
        }
    } else {
        processes[i].burstTimeRemaining -= quantum;
        ( * currentTime) += quantum;
        if ( * programsExecuted != n) {
            checkForNewArrivals(processes, n, * currentTime, readyQueue, queueSize);
        }
        readyQueue[ * queueSize] = i;
        ( * queueSize) ++;
    }
}
void output(struct Process processes[],
    const int n) {
    double avgWaitingTime = 0;
    double avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        printf("Process %d: Waiting Time: %d Turnaround Time: %d\n", processes[i].pid,processes[i].waitingTime,processes[i].turnaroundTime);
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    printf("Average Waiting Time: %.2lf\n", avgWaitingTime / n);
    printf("Average Turnaround Time: %.2lf\n", avgTurnaroundTime / n);
}
void roundRobin(struct Process processes[], int n, int quantum) {
    int readyQueue[n];
    int queueSize = 0;
    readyQueue[queueSize++] = 0;
    processes[0].inQueue = true;
    int currentTime = 0;
    int programsExecuted = 0;
    while (queueSize > 0) {
        updateQueue(processes, n, quantum, readyQueue, & queueSize, & currentTime, &
            programsExecuted);
    }
}
int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", & n);
    printf("Enter time quantum: ");
    scanf("%d", & quantum);
    struct Process processes[n + 1];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of each process %d: ", i + 1);
        scanf("%d %d", & processes[i].arrivalTime, & processes[i].burstTime);
        processes[i].burstTimeRemaining = processes[i].burstTime;
        processes[i].pid = i + 1;
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        processes[i].isComplete = false;
        processes[i].inQueue = false;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrivalTime < processes[i].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    roundRobin(processes, n, quantum);
    output(processes, n);
    return 0;
}