#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateMatix(int **arr, int n) {
    srand(time(NULL));

    int min = 2, max = 10;
    for (int i = 0; i < n; i++) {
        int m = min + rand() % (max - min + 1);
        arr[i] = malloc(sizeof(int) * m);
        arr[i][0] = m;

        for (int j = 1; j < m; j++) {
            arr[i][j] = rand() % 101;
        }
    }
}

void sum(int **a, int *b, int n) {
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int m = a[i][0];
        b[i] = 0;
        for (int j = 1; j < m; j++) {
            b[i] += a[i][j];
        }
    }
}

void printMatrix(int **arr, int n) {
    int m = 0;
    for (int i = 0; i < n; i++) {
        m = arr[i][0];
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 10, **a = malloc(sizeof(int*) * n), *b = malloc(sizeof(int) * n);

    generateMatix(a, n);
    printMatrix(a, n);
    sum(a, b, n);
    printArray(b, n);

    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
}