#include <stdio.h>

int main() {
    // for (k=0, m=1; m <= n; k++, m = m * 2);
    // printf(“%d”, k-1); }

    int n = 0, k = 0;
    scanf("%d", &n);

    for (int m = 1; m <= n; m = m * 2) {
        printf("%d", k-1); 
        k++;
    }

    // Выполняет цикл x = log2(n) + 1 раз
    // Выводит числа от -1 до x - 2
}