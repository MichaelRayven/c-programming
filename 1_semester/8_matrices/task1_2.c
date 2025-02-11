#include <stdio.h>

void replaceColumn(int size, int j1, float matrix[size][size], float constants[size], float (*buf)[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == j1) {
                (*buf)[i][j] = constants[i];
            } else {
                (*buf)[i][j] = matrix[i][j]; 
            }
        }
    }
}

void printMatrix(int size, float matrix[size][size]) {
    for (int i = 0; i < size; i++) {
        printf("\n");
        for (int j = 0; j < size; j++)
            printf("%.2f ", matrix[i][j]);
    }
    printf("\n\n");
}

void printArray(int size, float array[size]) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", array[i]);
    }
    printf("\n\n");
}

void copyMatrix(int size, float matrix[size][size], float (*buf)[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (*buf)[i][j] = matrix[i][j]; 
        }
    }
}

void getMinor(int size, int excRow, int excCol, float matrix[size][size], float (*buf)[size - 1][size - 1]) {
    int row = 0, col = 0;

    for (int i = 0; i < size; i++) {
        if (i == excRow) continue;

        for (int j = 0; j < size; j++) {
            if (j == excCol) continue;
            (*buf)[row][col] = matrix[i][j];
            col = (col + 1) % (size - 1);
        }
        row = (row + 1) % (size - 1);
    }
}

float computeDeterminant(int size, float matrix[size][size]) {
    switch (size)
    {
    case 1:
        return matrix[0][0];
        break;
    case 2:
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
        break;
    case 3:
        return matrix[0][0]*matrix[1][1]*matrix[2][2] + 
            matrix[0][1]*matrix[1][2]*matrix[2][0] +
            matrix[0][2]*matrix[1][0]*matrix[2][1] -
            matrix[0][2]*matrix[1][1]*matrix[2][0] -
            matrix[0][0]*matrix[1][2]*matrix[2][1] -
            matrix[0][1]*matrix[1][0]*matrix[2][2];
        break;
    default: ;
        float result = 0.0f;
        for (int j = 0; j < size; j++) {
            float tempMatrix[size - 1][size - 1];
            getMinor(size, 0, j, matrix, &tempMatrix);
            float det = computeDeterminant(size - 1, tempMatrix);

            if (j % 2 == 0) {
                result += det * matrix[0][j];
            } else {
                result -= det * matrix[0][j];
            }
        }
        return result;
        break;
    }
}

void solveSLAE(int size, float matrix[size][size], float constants[size], float (*buf)[size]) {
    float determinant = computeDeterminant(size, matrix);

    for (int i = 0; i < size; i++) {
        float xMatrix[size][size];
        replaceColumn(size, i, matrix, constants, &xMatrix);
        float xDeterminant = computeDeterminant(size, xMatrix);

        if (determinant == 0) {
            printf("Нет единственного решения.");
            break;
        }

        (*buf)[i] = xDeterminant/determinant;
    }

    printArray(size, *buf);
}

int main() {
    int N = 0;
    printf("Enter the number of unknowns: ");
    scanf("%d", &N);

    float matrix[N][N];
    float constants[N];
    float results[N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float multiplier = 0.0f;
            printf("Enter the coefficient for x_%d of the %d equation: ", j+1, i+1);
            scanf("%f", &multiplier);

            matrix[i][j] = multiplier;
        }
        float constant = 0.0f;
        printf("Enter the constant for %d equation: ", i+1);
        scanf("%f", &constant);

        constants[i] = constant;
    }

    solveSLAE(N, matrix, constants, &results);


    return 0;
}