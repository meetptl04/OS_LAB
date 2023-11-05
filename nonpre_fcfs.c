#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n];
    int arrtime[n];
    int burstime[n];
    int priority[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the process ID %d: ", (i + 1));
        scanf("%d", &process[i]);
        printf("Enter arrival time for process %d: ", (i + 1));
        scanf("%d", &arrtime[i]);
        printf("Enter burst time for process %d: ", (i + 1));
        scanf("%d", &burstime[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrtime[j] > arrtime[j + 1]) {
                int temp1 = arrtime[j];
                arrtime[j] = arrtime[j + 1];
                arrtime[j + 1] = temp1;

                int temp2 = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp2;

                int temp3 = burstime[j];
                burstime[j] = burstime[j + 1];
                burstime[j + 1] = temp3;
            }
        }
    }

    int tt[n];
    int bt[n];
    int sum1[n];
    int sum = arrtime[0];

    printf("P_ID\tC_T\tA_T\tB_T\tT_T\tW_T\n");

    for (int i = 0; i < n; i++) {
        sum += burstime[i];
        sum1[i] = sum;
        tt[i] = sum - arrtime[i];
        bt[i] = tt[i] - burstime[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n", process[i], sum, arrtime[i], burstime[i], tt[i], bt[i]);
    }

    printf("\nGantt Chart :");

    if (arrtime[0] > 0) {
        printf("0");
        for (int i = 0; i < arrtime[0]; i++) {
            printf("*");
        }
        printf("[%d]", arrtime[0]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < burstime[i]; j++) {
            printf("_");
        }
        printf("|P%d[%d]", process[i], sum1[i]);
    }

    printf("\n(Where * denotes IDEL TIME)");

    float avgtt = 0;
    float avgbt = 0;

    for (int i = 0; i < n; i++) {
        avgtt += tt[i];
        avgbt += bt[i];
    }

    printf("\nAverage TT: %f\n", avgtt / n);
    printf("Average BT: %f", avgbt / n);

    return 0;
}
