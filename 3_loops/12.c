#include <stdio.h>

int main() {
    // for (n=a, s=0; n!=0; n=n/10)
    //   { k=n%10; s=s+k;} 

    int k, a, s = 0;
    scanf("%d", &a);

    for (int n = a; n != 0; n = n / 10) { 
        k = n % 10; 
        s = s + k;
    } 

    printf("Sum of digits: %d", s);
}