#include <stdio.h>

int readfloat(char *message, float *ptr) {
    printf("%s", message);

    // Drain stdin line into a buffer
    // Scanf doesn't drain stdin buffer if it doesn't fit the format
    char line[64];
    fgets(line, sizeof(line), stdin);

    // Make sure that variables are assigned
    if (sscanf(line, "%f", ptr) != 1) {
        return 0;
    } else {
        return 1;
    }
}

float my_pow(float x, int e) {
    float result = 1;
    for (int i = 0; i < e; i++) {
        result *= x;
    }
    return result;
}

int factorial(int x) {
    int result = 1;
    for (int i = 0; i < (x - 1); i++) {
        result *= (x - i);
    }
    return result;
}

float arctg(float x, int n) {
    float result = 0;
    while (n >= 1) {
        float sign = my_pow(-1, n - 1);
        float denumerator = 2*n - 1;
        float numerator = my_pow(x, denumerator);
        result += sign*(numerator/denumerator);
        n--;
    }
    return result;
}

int main() {
    float x;
    do {
        x = 0;
        readfloat("Please enter the value of X: ", &x);
    } while (x < -1 || x > 1);

    float atg = arctg(x, 10);
    printf("The arctg(%.5f) is %.5f", x, atg);
}