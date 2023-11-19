#include<stdio.h>

struct process {
  int done;
  int pid;
  int allocation[4];
  int max[4];
  int need[4];
};
int main() {
  int n, i, j, k;
  int maxreso[4];
  printf("Enter the number of processes: ");
  scanf("%d", & n);
  int available[4];
  struct process p[n];
  int order[n];
  printf("Enter the details of the processes: ");
  for (i = 0; i < n; i++) {
    printf("Enter the details of p%d\n", i);
    p[i].pid = i;
    printf("Enter the allocation details: ");
    for (j = 0; j < 4; j++) {
      scanf("%d", & p[i].allocation[j]);
    }
    maxreso[0] += p[i].allocation[0];
    maxreso[1] += p[i].allocation[1];
    maxreso[2] += p[i].allocation[2];
    maxreso[3] += p[i].allocation[3];
    printf("Enter the max details: ");
    for (j = 0; j < 4; j++) {
      scanf("%d", & p[i].max[j]);
    }
    p[i].done = 0;
  }
  printf("Enter the available resources: ");
  for (i = 0; i < 4; i++) {
    scanf("%d", & available[i]);
  }
  maxreso[0] += available[0];
  maxreso[1] += available[1];
  maxreso[2] += available[2];
  maxreso[3] += available[3];
  printf("Maximum instances : \n");
  printf("A\tB\tC\tD\n");
  for (int i = 0; i < 4; i++) {
    printf("%d\t", maxreso[i]);
  }
  printf("\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < 4; j++) {
      p[i].need[j] = p[i].max[j] - p[i].allocation[j];
    }
  }
  printf("need matrix:\n");
  printf("A\tB\tC\tD\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < 4; j++) {
      printf("%d\t", p[i].need[j]);
    }
    printf("\n");
  }
  int c = 0;
  printf("\n");
  for (i = 0; i < 4; i++) {
    printf("%d\t", & available[i]);
  }
  printf("\n");
  int count = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (p[j].done != 1) {
        for (k = 0; k < 4; k++) {
          if (p[j].need[k] <= available[k]) {
            count += 1;
          }
        }
        if (count == 3) {
          order[c] = p[j].pid;
          c += 1;
          p[j].done = 1;
          for (k = 0; k < 4; k++) {
            available[k] += p[j].allocation[k];
          }
          // for (int i=0;i<4;i++){
          // printf("%d\t",available[k]);
          // }
        }
      }
      count = 0;
    }
  }
  int count1;
  for (i = 0; i < n; i++) {
    if (p[i].done == 1) {
      count1 += 1;
    }
  }
  if (count1 == n) {
    for (i = 0; i < n; i++) {
      printf("p%d ", order[i]);
    }
    printf("\nThe System is in safe state!");
  }
}