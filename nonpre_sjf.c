#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes:");
    scanf("%d", & n);
    int pid[n];
    int arrivalTimes[n];
    int burstTimes[n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter Process ID:");
        scanf("%d", & pid[i]);
        printf("Enter the arrival time:");
        scanf("%d", & arrivalTimes[i]);
        if (arrivalTimes[i] == 0) {
            count = count + 1;
        }
        printf("Enter the Burst time:");
        scanf("%d", & burstTimes[i]);
    }
    int temp1, temp2, temp3 = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrivalTimes[j] > arrivalTimes[j + 1]) {

                temp1 = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp1;

                temp2 = arrivalTimes[j];
                arrivalTimes[j] = arrivalTimes[j + 1];
                arrivalTimes[j + 1] = temp2;

                temp3 = burstTimes[j];
                burstTimes[j] = burstTimes[j + 1];
                burstTimes[j + 1] = temp3;
            }
        }
    }
    temp1, temp2, temp3 = 0;
    for (int i = 0; i < n - 1; i++) {
        if (count == n) {
            for (int j = 0; j < n - i - 1; j++) {
                if (burstTimes[j] > burstTimes[j + 1]) {

                    temp1 = pid[j];
                    pid[j] = pid[j + 1];
                    pid[j + 1] = temp1;

                    temp2 = arrivalTimes[j];
                    arrivalTimes[j] = arrivalTimes[j + 1];
                    arrivalTimes[j + 1] = temp2;

                    temp3 = burstTimes[j];
                    burstTimes[j] = burstTimes[j + 1];
                    burstTimes[j + 1] = temp3;
                }
            }
        } else {
            for (int j = count; j < n - i - 1; j++) {
                if (burstTimes[j] > burstTimes[j + 1]) {
                    temp1 = pid[j];
                    pid[j] = pid[j + 1];
                    pid[j + 1] = temp1;

                    temp2 = arrivalTimes[j];
                    arrivalTimes[j] = arrivalTimes[j + 1];
                    arrivalTimes[j + 1] = temp2;

                    temp3 = burstTimes[j];
                    burstTimes[j] = burstTimes[j + 1];
                    burstTimes[j + 1] = temp3;
                }
            }
        }
    }
    // for (int i = 0; i < n - 1; i++) {
    // for (int j = 0; j < count - i - 1; j++) {
    // if (burstTimes[j] > burstTimes[j + 1]) {
    // temp1 = pid[j];
    // pid[j] = pid[j + 1];
    // pid[j + 1] = temp1;
    // temp2 = arrivalTimes[j];
    // arrivalTimes[j] = arrivalTimes[j + 1];
    // arrivalTimes[j + 1] = temp2;
    // temp3 = burstTimes[j];
    // burstTimes[j] = burstTimes[j + 1];
    // burstTimes[j + 1] = temp3;
    // }
    // }
    // }
    int sum = arrivalTimes[0];
    int tt = 0;
    int turnaroundTimes[n];
    int waitingTimes[n];
    int finishTimes[n];
    for (int i = 0; i < n; i++) {
        sum = sum + burstTimes[i];
        finishTimes[i] = sum;
    }
    float avgTurnaroundTime = 0;
    float avgWaitingTime = 0;
    int wt = 0;
    for (int i = 0; i < n; i++) {
        tt = finishTimes[i] - arrivalTimes[i];
        turnaroundTimes[i] = tt;
        wt = tt - burstTimes[i];
        waitingTimes[i] = wt;
        avgWaitingTime = avgWaitingTime + wt;
        avgTurnaroundTime = avgTurnaroundTime + tt;
    }
    printf("PID\tF_T\tA_T\tB_T\tT_T\tW_T\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n", pid[i], finishTimes[i],arrivalTimes[i], burstTimes[i], turnaroundTimes[i], waitingTimes[i]);
    }
    printf("\nGantt Chart :\n");
    if (arrivalTimes[0] >= 0) {
        printf("0");
        for (int i = 0; i < arrivalTimes[0]; i++) {
            printf("*");
        }
        printf("[%d]", arrivalTimes[0]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstTimes[i]; j++) {
            printf("_");
        }
        printf("|P%d[%d]", pid[i], finishTimes[i]);
    }
    printf("\n(Where * denotes IDLE TIME)\n");
    printf("Average Turnaround Time = %.2f\n", avgTurnaroundTime / n);
    printf("Average Waiting Time = %.2f\n", avgWaitingTime / n);
    return 0;
}