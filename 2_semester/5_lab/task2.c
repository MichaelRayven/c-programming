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

int **createMatrix(int m) {
    int **a = (int **) malloc(sizeof(int*) * m);

    if (a == NULL) {
        return NULL;
    } else {
        for (int i = 0; i < m; i++) {
            a[i] = (int *) malloc(sizeof(int) * (i + 1));

            if (a[i] == NULL) {
                return NULL;
            }

            for (int j = 0; j < (i + 1); j++) {
                a[i][j] = (i + 1) * (j + 1);
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

void printMatrix(int m, int **arr) {
    for (int i = 0; i < m; i++) {
        printf("%3d", arr[i][0]);
        for (int j = 1; j < (i + 1); j++) {
            printf(", %3d", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* arvg[]) {
    int m = 9;
    printf("Enter the size of the table: ");
    readInt(&m);

    int **A = createMatrix(m);
    
    printf("\nThe multiplication table of size %d: \n", m);
    printMatrix(m, A);

    destroyMatrix(m, A);

    return 0;
}