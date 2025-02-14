#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readInt(int *number){
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

int **createMatrix(int m, int n) {
    int **a = (int **) malloc(sizeof(int*) * m);

    if (a == NULL) {
        return NULL;
    } else {
        for (int i = 0; i < m; i++) {
            a[i] = (int *) malloc(sizeof(int) * n);

            if (a[i] == NULL) {
                return NULL;
            }

            for (int j = 0; j < n; j++) {
                a[i][j] = 0;
            }
        }
    }

    return a;
}

void destroyMatrix(int m, int **arr) {
    for (int i = 0; i < m; i++) {
        free(arr[i]);
    }
    free(arr);
}

void fillRand(int m, int n, int **arr) {
    srand(time(NULL));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % (100 + 1);
        }
    }
}

void printMatrix(int m, int n, int **arr) {
    for (int i = 0; i < m; i++) {
        printf("%3d", arr[i][0]);
        for (int j = 1; j < n; j++) {
            printf(", %3d", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* arvg[]) {
    int k = 10, m = 10, n;

    printf("Enter the value of m: ");
    readInt(&m);
    printf("Enter the value of k: ");
    readInt(&k);

    if (m % k == 0) {
        n = m*m / k;
    } else {
        n = m*m / k + 1;
    }

    int **B = createMatrix(n, k), **A = createMatrix(m, m);
    if (A == NULL || B == NULL) {
        printf("Memory allocation failed");
        return 1;
    }

    fillRand(m, m, A);

    for (int i = 0; i < m*m; i++) {
        B[i / k][i % k] = A[i / m][i % m];
    }
    
    printf("\nThe initial array A: \n");
    printMatrix(m, m, A);
    printf("The new array B: \n");
    printMatrix(n, k, B);

    destroyMatrix(m, A);
    destroyMatrix(n, B);

    return 0;
}