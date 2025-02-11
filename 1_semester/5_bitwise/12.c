#include <stdio.h>

void printBytes(int size, int num);

int main(void) 
{
    unsigned int a;
    do 
    {
        printf("Please enter a two or more byte integer: ");
        scanf("%u", &a);
    } while (a < 256);

    int firstByte = (a << 24) >> 24;
    int secondByte = (a << 16) >> 24;

    int result = (a >> 16) << 8;
    result = (result | firstByte) << 8;
    result = result | secondByte;
    printf("Original: ");
    printBytes(4, a);
    printf("Modified: ");
    printBytes(4, result);
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