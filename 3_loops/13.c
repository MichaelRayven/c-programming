#include <stdio.h>

int main() {
    // for (s=1, i=0; i<=n; i++) s = s * 2;

    int n, s = 1;
    scanf("%d", &n);

    for (int i=0; i <= n; i++) 
        s = s * 2;

    printf("2 to the power of %d: %d", n + 1, s);
    // 2 в степени n + 1
}