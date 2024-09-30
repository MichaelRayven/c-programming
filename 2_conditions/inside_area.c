#include <stdio.h>
#include <math.h>

int main() {
    float x = 0, y = 0;

    printf("Enter coordinates (x,y): ");
    scanf("%f%*c%f", &x, &y);

    if (x > 0 && x*x + y*y > 1 && x*x + y*y < 4) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Math implementation
    // if (x > 0 && pow(x, 2) + pow(y, 2) > 1 && pow(x, 2) + pow(y, 2) < 4) {
    //     printf("YES\n");
    // } else {
    //     printf("NO\n");
    // }

    
}