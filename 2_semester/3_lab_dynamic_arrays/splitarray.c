#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readInt(int *number) {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

void printArray(int *arr, int n) {
    if (n > 0) {
        printf("%d", arr[0]);
        for (int i = 1; i < n; i++) {
            printf(", %d", arr[i]);
        }
        puts("\n");
    }
}

int main() {
    // Random seed
    srand(time(NULL));

    printf("Enter the size of the array: ");
    int n = 0;
    readInt(&n);

    int *b = (int *) malloc(n*sizeof(int));
    int min = -50, max = 50;

    int m = 0, k = 0;
    for (int i = 0; i < n; i++) {
        b[i] = rand() % (max + 1 - min) + min;
        if (b[i] >= 0) {
            m++;
        } else {
            k++;
        }
    }

    int *c = (int *) malloc(m*sizeof(int));
    int *d = (int *) malloc(k*sizeof(int));

    int negi = 0, posi = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] >= 0) {
            c[posi] = b[i];
            posi++;
        } else {
            d[negi] = b[i];
            negi++;
        }
    }

    printf("The initial array of length %d: \n", n);
    printArray(b, n);

    printf("Positive integers array of length %d: \n", m);
    printArray(c, m);
    
    printf("Negative integers array of length %d: \n", k);
    printArray(d, k);

    free(b);
    b = NULL;
    free(c);
    c = NULL;
    free(d);
    d = NULL;

    return 0;
}