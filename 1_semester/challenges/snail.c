#include <stdio.h>
#include <string.h>

void printMatrix(int size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%02d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int readint(char *message, int *ptr) {
    printf("%s", message);

    // Drain stdin line into a buffer
    // Scanf doesn't drain stdin buffer if it doesn't fit the format
    char line[64];
    fgets(line, sizeof(line), stdin);

    // Make sure that variables are assigned
    if (sscanf(line, "%d", ptr) != 1) {
        return 0;
    } else {
        return 1;
    }
}

void fillMatrix(int size, int matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }
}

int main() {
    int size = 0;
    do {
        readint("Enter the size of the matrix: ", &size);
    } while (size <= 0);
    
    int matrix[size][size];
    fillMatrix(size, matrix);
    printMatrix(size, matrix);

    int directions[4][2] = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };
    for (int num = 1, i = 0, j = 0, dind = 0; num <= size*size; num++) {
        printf("%d,%d\n", i, j);
        matrix[i][j] = num;
        int newi = i + directions[dind][0];
        int newj = j + directions[dind][1];

        if (newi >= size || newj >= size || newi < 0 || newj < 0 || matrix[newi][newj] != 0) {
            dind = (dind + 1) % 4;
            newi = i + directions[dind][0];
            newj = j + directions[dind][1];
        }
        i = newi;
        j = newj;
    }

    printMatrix(size, matrix);
    printf("Size: %d", size);

    return 0;
}