#include <stdio.h>

void printPageFrames(int pageFrames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (pageFrames[i] == -1) {
            printf(" - ");
        } else {
            printf("%2d ", pageFrames[i]);
        }
    }
    printf("\n");
}

int findLRU(int pageFrames[], int numFrames, int reference[], int n, int currentIndex) {
    int lru = -1;
    int farthestIndex = currentIndex;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex - 1; j >= 0; j--) {
            if (pageFrames[i] == reference[j]) {
                if (j < farthestIndex) {
                    farthestIndex = j;
                    lru = i;
                }
                break;
            }
        }
        if (j == -1) {
            return i;
        }
    }
    return (lru == -1) ? 0 : lru;
}

int pageFaultsFIFO(int reference[], int n, int MAX_FRAMES) {
    int pageFrames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1;
    }
    
    int currentIndex = 0;

    for (int i = 0; i < n; i++) {
        int page = reference[i];
        int isPageInFrame = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageFrames[j] == page) {
                isPageInFrame = 1;
                break;
            }
        }

        if (!isPageInFrame) {
            if (currentIndex == MAX_FRAMES) {
                currentIndex = 0;
            }
            pageFrames[currentIndex] = page;
            currentIndex++;
            pageFaults++;
            printf("Page reference %2d: ", page);
            printPageFrames(pageFrames, MAX_FRAMES);
        }
    }

    return pageFaults;
}

int pageFaultsLRU(int reference[], int n, int MAX_FRAMES) {
    int pageFrames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = reference[i];
        int isPageInFrame = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageFrames[j] == page) {
                isPageInFrame = 1;
                break;
            }
        }

        if (!isPageInFrame) {
            int lru = findLRU(pageFrames, MAX_FRAMES, reference, n, i);
            pageFrames[lru] = page;
            pageFaults++;
            printf("Page reference %2d: ", page);
            printPageFrames(pageFrames, MAX_FRAMES);
        }
    }

    return pageFaults;
}

int pageFaultsOptimal(int reference[], int n, int MAX_FRAMES) {
    int pageFrames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        pageFrames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = reference[i];
        int isPageInFrame = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (pageFrames[j] == page) {
                isPageInFrame = 1;
                break;
            }
        }

        if (!isPageInFrame) {
            int farthestIndex = i;
            int replaceIndex = -1;

            for (int j = 0; j < MAX_FRAMES; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (pageFrames[j] == reference[k]) {
                        if (k > farthestIndex) {
                            farthestIndex = k;
                            replaceIndex = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1) {
                replaceIndex = 0;
            }

            pageFrames[replaceIndex] = page;
            pageFaults++;
            printf("Page reference %2d: ", page);
            printPageFrames(pageFrames, MAX_FRAMES);
        }
    }

    return pageFaults;
}

int main() {
    int n;
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int reference[n];
    int MAX_FRAMES;

    printf("Enter the frame size: ");
    scanf("%d", &MAX_FRAMES);

    printf("Enter the references: ");
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        reference[i] = x;
    }

    printf("FIFO Page Replacement:\n");
    int fifoPageFaults = pageFaultsFIFO(reference, n, MAX_FRAMES);
    printf("Total page faults for FIFO: %d\n", fifoPageFaults);

    printf("\nLRU Page Replacement:\n");
    int lruPageFaults = pageFaultsLRU(reference, n, MAX_FRAMES);
    printf("Total page faults for LRU: %d\n", lruPageFaults);

    printf("\nOptimal Page Replacement:\n");
    int optimalPageFaults = pageFaultsOptimal(reference, n, MAX_FRAMES);
    printf("Total page faults for Optimal: %d\n", optimalPageFaults);

    if (fifoPageFaults <= lruPageFaults && fifoPageFaults <= optimalPageFaults) {
        printf("\nFIFO has the fewest page faults.\n");
    } else if (lruPageFaults <= fifoPageFaults && lruPageFaults <= optimalPageFaults) {
        printf("\nLRU has the fewest page faults.\n");
    } else {
        printf("\nOptimal has the fewest page faults.\n");
    }

    return 0;
}
