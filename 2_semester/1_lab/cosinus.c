#include <stdio.h>
#include <stdio.h>
#include <math.h>

int readInt(int *number) {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

int readFloat(float *number) {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%f", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

float my_pow(float x, int n) {
    float result = 1.0f;

    if (n == 0) {
        return 1.0f;
    } else {
        for (int i = 0; i < n; i++) {
            result *= x;
        }

        if (n > 0) {
            return result;
        } else {
            return 1.0f / result;
        }
    }
}

int factorial(int x) {
    int result = 1;

    for (int i = 1; i <= x; i++) {
        result *= i;
    }

    return result;
}

float cosinus(float x) {
    float eps = 0.0001f;
    float result = 0.0f;
    float r = 0.0f;
    int n = 0;

    do {
        r = my_pow(x, n*2) / factorial(2*n);
        result += my_pow(-1, n) * r;
        n++;
    } while(r >= eps);

    return result;
}

void main() {
    printf("Enter the value of x: ");
    float x = 0;
    readFloat(&x);

    printf("cosinus(x) = %f\n", cosinus(x));
    printf("cos(x) = %f\n", cos(x));
}