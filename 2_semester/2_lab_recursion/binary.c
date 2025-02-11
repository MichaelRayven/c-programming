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

void toBinary(int x) {
    if (x > 0) {
        toBinary(x / 2);
        printf("%d", x % 2);
    }
}

void main() {
    printf("Enter a decimal integer: ");
    int x = 0;
    readInt(&x);

    toBinary(x);
}