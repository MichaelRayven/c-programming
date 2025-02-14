#include <stdio.h>
#include <math.h>

typedef struct Triangle {
    float a;
    float b;
    float c;
} Triangle;

int readFloat(float *number){
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%f", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

/*
    Calculates the perimeter and area of a given triangle.

    @param t Triangle struct pointer.
    @param p Pointer to the perimeter variable.
    @param a Pointer to the area variable.
    @returns 0 on success, 1 if the triangle doesn't exist.
*/
int perimeterArea(Triangle *t, float *p, float *a) {
    // (*t).a is equivalent to t->a
    *p = t->a + t->b + t->c;
    *a = (float) sqrt(*p * 
        (*p - 2 * t->a) * 
        (*p - 2 * t->b) * 
        (*p - 2 * t->c)) / 4;

    if (t->a + t->b > t->c || 
        t->a + t->c > t->b ||
        t->c + t->b > t->a) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    float a = 0, b = 0, c = 0, perimeter = 0, area = 0;

    printf("Enter length of the side A: ");
    readFloat(&a);

    printf("Enter length of the side B: ");
    readFloat(&b);

    printf("Enter length of the side C: ");
    readFloat(&c);

    Triangle tr = {.a = a, .b = b, .c = c};

    // printf("Triangle sides: %f, %f, %f\n", a, b, c);
    // printf("Triangle sides: %f, %f, %f\n", tr.a, tr.b, tr.c);
    int result = perimeterArea(&tr, &perimeter, &area);

    if (result == 1) {
        printf("This triangle is impossible!");
        return 1;
    } else {
        printf("The perimeter of the triangle is: %.3f\n", perimeter);
        printf("The area of the triangle is: %.3f\n", area);
    }
}