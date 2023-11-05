#include<stdio.h>

int main() {
    int a[10], b[10], x[10];
    int waiting[10], turnaround[10], completion[10], p[10];
    int i, j, smallest, count = 0, time, n;
    double avg = 0, tt = 0, end;
    printf("\nEnter the number of Processes: ");
    scanf("%d", & n);
    printf("\nEnter arrival time of processes: ");
    for (i = 0; i < n; i++) {
        scanf("%d", & a[i]);
    }
    printf("\nEnter burst time of processes: ");
    for (i = 0; i < n; i++) {

        scanf("%d", & b[i]);
    }
    printf("\nEnter priority of processes: ");
    for (i = 0; i < n; i++) {

        scanf("%d", & p[i]);
    }
    for (i = 0; i < n; i++)
        x[i] = b[i];
    p[9] = -1;
    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (a[i] <= time && p[i] > p[smallest] && b[i] > 0)
                smallest = i;
        }
        b[smallest]--;
        if (b[smallest] == 0) {
            count++;
            end = time + 1;
            completion[smallest] = end;
            waiting[smallest] = end - a[smallest] - x[smallest];
            turnaround[smallest] = end - a[smallest];
        }
    }
    printf("Process\tburst-time\tarrival-time\twaiting-time\tturnaround-time\tcompletion-time\tPriority\
n");

    for (i = 0; i < n; i++) {
        printf("p%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, x[i], a[i], waiting[i], turnaround[i],
            completion[i], p[i]);
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
    printf("\n\nAverage waiting time = %.2lf", avg / n);
    printf("\nAverage Turnaround time = %.2lf\n", tt / n);
    return 0;
}