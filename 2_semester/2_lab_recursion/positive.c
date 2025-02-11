#include <stdio.h>
#include <stdio.h>

int readInt(int *number) {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

void printPositive() {
    int x = 0;
    readInt(&x);
    if (x == 0) {
        return;
    } else {
        printPositive();
        if (x > 0) {
            printf("%d ", x);
        }
    }
}

void main() {
    printf("Enter an integer sequence that ends with zero: ");
    printPositive();
    printf("\n");
}