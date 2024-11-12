#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int a, int b, float** matrix) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

float** allocateMatrix(int a, int b) {
    float** matrix = (float**) malloc(a * sizeof(float*));
    for (int i = 0; i < b; i++)
        matrix[i] = (float*) malloc(b * sizeof(float));
    return matrix;
}

void deleteMatrix(int size, float **matrix) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Транспонирование
float** transpose(int size, float** matrix) {
    float **newMatrix = allocateMatrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[j][i];
        }
    }
    return newMatrix;
}

// Максимальный элемент
float findMatrixMax(int a, int b, float** matrix) {
    float max = -9999999999;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
    }
    return max;
}

// Среднее арифметическое
float findMatrixAvg(int a, int b, float** matrix) {
    float sum = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            sum += matrix[i][j];
        }
    }
    return sum / (a*b);
}

// Получить квадрат
float** getMaxSquare(int a, int b, float** matrix) {
    float max = findMatrixMax(a, b, matrix);

    int maxI = 0, maxJ = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (max == matrix[i][j]) {
                maxI = i;
                maxJ = j;
                break;
            }
        }
    }

    printf("%.2f: %d, %d ", max, maxI, maxJ);

    int squareSize = 0;
    if (maxI > maxJ) {
        squareSize = maxJ + 1;
    } else {
        squareSize = maxI + 1;
    }
    float **square = allocateMatrix(squareSize, squareSize);

    for (int i = 0; i < squareSize; i++) {
        for (int j = 0; j < squareSize; j++) {
            // Check for exceptions
            // printf("%d, %d ", i, j);
            square[i][j] = matrix[maxI - (squareSize - 1) + i][maxJ - (squareSize - 1) + j];
        }
    }

    return square;
}

int randRange(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

float** randomSquareMatrix(int size) {
    float** matrix = allocateMatrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = randRange(-100, 100);
        }
    }
    return matrix;
}

// 3. Транспонировать в матрице квадрат, в правом нижнем углу которого расположен максимальный элемент. 
// Определить среднее арифметическое значение исходной матрицы и транспонированного квадрата отдельно. 
// Заменить нули в матрице на скаляр, введенный с клавиатуры.

int main() {
    int size = 10;
    srand(time(NULL));
    float** matrix = randomSquareMatrix(size);

    // float max = findMatrixMax(size, size, matrix);
    // printMatrix(size, size, matrix);
    // printf("%.2f", max);

    float** square = getMaxSquare(size, size, matrix);
    float** squareTransposed = transpose(size, square);
    
    printf("The matrix is:\n");
    printMatrix(size, size, matrix);

    return 0;
}