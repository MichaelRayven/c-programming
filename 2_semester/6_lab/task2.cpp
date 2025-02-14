#include <stdio.h>
#include <math.h>

const float p = 0.45f, q = 1 - p;

int readInt(int *number){
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

int factorial(int n) {
    int result = 1;
    for (int i = n; i > 1; i--) {
        result *= i;
    }
    return result;
}

int combinations(int n, int m) {
    return factorial(n)/(factorial(m)*factorial(n-m));
}

void calculateProbability(int n, int m, float &pd, float &pm) {
    float c = combinations(n, m);
    pm = c * pow(q, m) * pow(p, n-m);
    pd = c * pow(p, m) * pow(q, n-m);
}

int main() {
    
    int n = 0, m = 0;
    float pd = 0, pm = 0;

    while (1)
    {
        printf("Enter the number of children: ");
        readInt(&n);

        printf("Enter the value of m: ");
        readInt(&m);

        if (n <= 0 || m <= 0 || m > n) {
            printf("Incorrect data, please try again.\n");
        } else {
            break;
        }
    }
    
    calculateProbability(n, m, pd, pm);

    printf("The probability of having %d girls out of %d children: %.6f\n", m, n, pd);
    printf("The probability of having %d boys out of %d children: %.6f\n", m, n, pm);
    printf("The probability of having %d boys or girls out of %d children: %.6f\n", m, n, pm + pd);
}