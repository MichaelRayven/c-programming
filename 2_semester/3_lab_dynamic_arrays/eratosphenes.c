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

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sieveOfEratosphenes(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] != 0) {
            printf("%d ", arr[i]);
            for (int j = arr[i] * arr[i] - 1; j < n; j += arr[i]) {
                arr[j] = 0;
            }
        }
    }
}

int main() {
    printf("Enter the size of the array: ");
    int n = 0, i;
    readInt(&n);

    int *b = (int *) malloc(n*sizeof(int));
    for (i = 0; i < n; i++) {
        b[i] = i + 1;
    }

    // printArray(b, n);
    // The array b has to be sorted 
    sieveOfEratosphenes(b, n);
    
    free(b);
    b = NULL;

    return 0;
}