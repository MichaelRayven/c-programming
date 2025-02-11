#include <stdio.h>

void printBytes(int size, int num);

int main(void) 
{
    int a;
    printf("Please enter an number: ");
    scanf("%d", &a);

    if ((((a - 1) & a) == 0) && a != 0) {
        printf("The number %d is a power of two", a);
    } else {
        printf("The number %d is not a power of two", a);
    }
}

void printBytes(int size, int num) {
    for (int i = 0; i < size; i++) {
        for (int j = 1; j <= 8; j++) {
            int bit = (num >> size * 8 - (j + i * 8)) & 1;
            printf("%u", bit);
        }
        printf(" ");
    }
    printf("\n");
}