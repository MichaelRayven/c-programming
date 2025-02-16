#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void zeroMinRange(int arr[], int n) {
    int minI = 0, minJ = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < arr[minI]) {
            minJ = minI;
            minI = i;
        } else if (arr[i] <= arr[minJ]) {
            minJ = i;
        }
    }

    if (minI > minJ) {
        int temp = minI;
        minI = minJ;
        minJ = temp;
    }

    for (int i = minI; i <= minJ; i++) {
        arr[i] = 0;
    }
}

void fillRand(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (100 + 1);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 10, a[10] = {0, 57, 11, 67, 3, 75, 41, 0, 94, 38};
    // fillRand(a, n);
    printArray(a, n);
    zeroMinRange(a, n);
    printArray(a, n);
}