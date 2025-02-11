#include <stdio.h>

int main() {    
    // for (n=2; n<a; n++)
    //      { if (a%n==0) break; }
    // if (n==a) puts("Good");	

    int a, n;
    printf("Enter a prime number: ");
    scanf("%d", &a);
    
    for (n = 2; n < a; n++) { 
        if (a % n == 0) 
            break; 
    }
    if (n == a) 
        printf("Good");	

    // Алгоритм поиска простых чисел
}