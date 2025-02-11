#include <stdio.h>

int main() {
    float temperature;
    char sign;

    printf("Input temperature: ");
    scanf("%f%c", &temperature, &sign);

    if (sign == 'c' || sign == 'C') {
        float fahrenheit = temperature * 9.0/5.0 + 32;
        printf("Output temperature: %.1ff\n", fahrenheit);

        return 0;
    }

    if (sign == 'f' || sign == 'F') {
        float celsius = (temperature - 32) * 5.0/9.0;
        printf("Output temperature: %.1fc\n", celsius);

        return 0;
    }

    printf("Output error\n");
}