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
            printf("%.1f ", matrix[i][j]);
    }
    printf("\n\n");
}

void printArray(int size, float array[size]) {
    for (int i = 0; i < size; i++) {
        printf("%.1f ", array[i]);
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
    // Declarations do not count as statements, C this is plain stupid
    // Aha, but this does "default: ;" - empty statement
    // I don't even know what to say  
    default: ;
        // Create a copy of the matrix to avoid altering the original
        float tempMatrix[size][size];

        copyMatrix(size, matrix, &tempMatrix);
        
        for (int i = 0; i < size; i++) {
            // Gauss's rule

            // float denominator = matrix[i][i];
            // for (int j = 0; j < size; j++) {
            //     matrix[i][j] /= denominator;
            // }

            // for (int j = 0; j < size; j++) {
            //     if (j == i) continue;
            //     float mult = matrix[j][i];

            //     for (int k = 0; k < size; k++) {
            //         if (k == i) {
            //             matrix[j][k] = 0;
            //         } else {
            //             matrix[j][k] -= matrix[i][k]*mult;
            //         }
            //     }
            // }

            for (int j = i + 1; j < size; j++) {
                if (j == i) continue;
                float mult = tempMatrix[j][i]/tempMatrix[i][i];

                // If matrix[i][i] == 0 trouble awaits
                if (tempMatrix[i][i] == 0.0f) {
                    printf("matrix[i][i] == 0 in `computeDeterminant`");
                }

                for (int k = 0; k < size; k++) {
                    if (k == i) {
                        tempMatrix[j][k] = 0;
                    } else {
                        tempMatrix[j][k] = tempMatrix[j][k] - tempMatrix[i][k]*mult;
                    }
                }
            }
        }
        
        float result = tempMatrix[0][0];
        for (int i = 1; i < size; i++) {
            result *= tempMatrix[i][i];
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

    // computeDeterminant(4, matrix);
    // printMatrix(4, matrix);

    // float buffer[4][4];

    // replaceColumn(4, 1, matrix, constants, &buffer);
    // printMatrix(4, buffer);

    solveSLAE(N, matrix, constants, &results);


    return 0;
}