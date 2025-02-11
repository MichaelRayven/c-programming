#include <stdio.h>

int main() {
    // for (s=0,n=2; n<a; n++)
    //      { if (a%n==0) s++; }
    // if (s==0) puts("Good");

    int a, s = 0;
    printf("Enter a prime number: ");
    scanf("%d", &a);
        
    for (int n = 2; n < a; n++) { 
        if (a % n == 0) s++; 
    }
        
    if (s == 0) printf("Good");
        
    // Алгоритм поиска простого числа
}