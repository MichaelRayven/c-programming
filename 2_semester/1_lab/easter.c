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

void main() {
    printf("Enter the year: ");
    int year = 0;
    readInt(&year);

    int a = year % 19;
    int b = year % 4;
    int c = year % 7;
    int d = (19*a + 15) % 30;
    int e = (2*b + 4*c + 6*d + 6) % 7;
    int f = d + e;

    if (f <= 26) {
        printf("Easter of %d is on %d of april\n", year, 4 + f);
    } else {
        printf("Easter of %d is on 26 of may\n", year);
    }
}