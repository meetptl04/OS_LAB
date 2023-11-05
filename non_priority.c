#include <stdio.h>

int main() {
    printf("Enter the number of processes:");
    int numProcesses, i, j, k;
    scanf("%d", & numProcesses);
    int processId[numProcesses];
    int arrivalTime[numProcesses];
    int burstTime[numProcesses];
    int priority[numProcesses];
    printf("Enter the process IDs in order:\n");
    for (i = 0; i < numProcesses; i++) {
        scanf("%d", & processId[i]);
    }
    printf("Enter the arrival time of the processes:\n");
    for (i = 0; i < numProcesses; i++) {
        scanf("%d", & arrivalTime[i]);
    }
    printf("Enter the burst time of the processes:\n");
    for (i = 0; i < numProcesses; i++) {
        scanf("%d", & burstTime[i]);
    }
    printf("Enter the priority level of the processes!\n(The higher the number the higher the priority!)\n");
    for (i = 0; i < numProcesses; i++) {
        scanf("%d", & priority[i]);
    }
    int count = 0;
    int initialArrivalTime;
    initialArrivalTime = arrivalTime[0];
    for (i = 0; i < numProcesses; i++) {
        if (arrivalTime[i] == initialArrivalTime) {
            count += 1;
        }
    }
    if (count == numProcesses) {
        for (i = 0; i < numProcesses; i++) {
            for (j = 0; j < numProcesses - 1; j++) {
                if (priority[j] < priority[j + 1]) {
                    int temp;
                    temp = arrivalTime[j];
                    arrivalTime[j] = arrivalTime[j + 1];
                    arrivalTime[j + 1] = temp;

                    temp = processId[j];
                    processId[j] = processId[j + 1];
                    processId[j + 1] = temp;

                    temp = burstTime[j];
                    burstTime[j] = burstTime[j + 1];
                    burstTime[j + 1] = temp;

                    temp = priority[j];
                    priority[j] = priority[j + 1];
                    priority[j + 1] = temp;
                }
            }
        }
    } else {
        for (i = 0; i < numProcesses; i++) {
            for (j = 0; j < numProcesses - 1; j++) {
                if (arrivalTime[j] > arrivalTime[j + 1]) {
                    int temp;
                    temp = arrivalTime[j];
                    arrivalTime[j] = arrivalTime[j + 1];
                    arrivalTime[j + 1] = temp;

                    temp = processId[j];
                    processId[j] = processId[j + 1];
                    processId[j + 1] = temp;

                    temp = burstTime[j];
                    burstTime[j] = burstTime[j + 1];
                    burstTime[j + 1] = temp;

                    temp = priority[j];
                    priority[j] = priority[j + 1];
                    priority[j + 1] = temp;
                }
            }
        }
        for (i = 0; i < numProcesses; i++) {
            for (j = 1; j < numProcesses - 1; j++) {
                if (priority[j] < priority[j + 1]) {
                    int temp;
                    temp = arrivalTime[j];
                    arrivalTime[j] = arrivalTime[j + 1];
                    arrivalTime[j + 1] = temp;

                    temp = processId[j];
                    processId[j] = processId[j + 1];
                    processId[j + 1] = temp;

                    temp = burstTime[j];
                    burstTime[j] = burstTime[j + 1];
                    burstTime[j + 1] = temp;

                    temp = priority[j];
                    priority[j] = priority[j + 1];
                    priority[j + 1] = temp;
                    
                } else if (priority[j] == priority[j + 1]) {
                    int temp;
                    if (arrivalTime[j] > arrivalTime[j + 1]) {

                        temp = arrivalTime[j];
                        arrivalTime[j] = arrivalTime[j + 1];
                        arrivalTime[j + 1] = temp;

                        temp = processId[j];
                        processId[j] = processId[j + 1];
                        processId[j + 1] = temp;

                        temp = burstTime[j];
                        burstTime[j] = burstTime[j + 1];
                        burstTime[j + 1] = temp;

                        temp = priority[j];
                        priority[j] = priority[j + 1];
                        priority[j + 1] = temp;
                    }
                }
            }
        }
    }
    int startTime[numProcesses];
    int endTime[numProcesses];
    int turnaroundTime[numProcesses];
    startTime[0] = arrivalTime[0];
    endTime[0] = startTime[0] + burstTime[0];
    printf("%d", startTime[0]);
    int midTime;
    midTime = endTime[0] / 2;
    for (i = 0; i < midTime; i++) {
        printf("_");
    }
    printf("P%d", processId[0]);
    for (i = 0; i < endTime[0] - midTime; i++) {
        printf("_");
    }
    printf("%d", endTime[0]);
    turnaroundTime[0] = endTime[0] - arrivalTime[0];
    for (i = 1; i < numProcesses; i++) {
        startTime[i] = endTime[i - 1];
        endTime[i] = endTime[i - 1] + burstTime[i];
        turnaroundTime[i] = endTime[i] - arrivalTime[i];
        midTime = endTime[i] / 2;
        for (j = 0; j < midTime; j++) {
            printf("_");
        }
        printf("P%d", processId[i]);
        for (j = 0; j < endTime[i] - midTime; j++) {
            printf("_");
        }
        printf("%d", endTime[i]);
    }
    printf("\nThe average turnaround time is: ");
    float totalTurnaroundTime = 0;
    float averageTurnaroundTime;
    for (i = 0; i < numProcesses; i++) {
        totalTurnaroundTime += turnaroundTime[i];
    }
    averageTurnaroundTime = totalTurnaroundTime / numProcesses;
    printf("%f\n", averageTurnaroundTime);
    int waitingTime[numProcesses];
    totalTurnaroundTime = 0;
    averageTurnaroundTime = 0;
    for (i = 0; i < numProcesses; i++) {
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        totalTurnaroundTime += waitingTime[i];
    }
    averageTurnaroundTime = totalTurnaroundTime / numProcesses;
    printf("The average waiting time is: %f\n", averageTurnaroundTime);
    return 0;
}