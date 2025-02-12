#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(float* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_ind = i;

        for (int j = i + 1; j < n; j++) {
            if (*arr[min_ind] > *arr[j]) {
                min_ind = j;
            }
        }

        float* temp = arr[i];
        arr[i] = arr[min_ind];
        arr[min_ind] = temp;
    }
}

void printArray(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void printArray(float* arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", *arr[i]);
    }
    printf("\n");
}

main()
{
    srand(time(NULL));

    int i,n; 
    float *a, **b;

    printf ("Enter the size of the array -> "); 
    scanf ("%d", &n);

    a = new float [n];
    b = new float* [n];

    if ( a == NULL || b == NULL ) {  
        printf(" Не удалось выделить память ");
        return 1; 
    }

    // Initiate the array
    for (i = 0; i < n; i ++ ) { 
        a[i] = ((float) rand() / ((float) RAND_MAX / 1000));
        b[i] = a + i;
    }

    // Sort the array
    selectionSort(b, n);

    printArray(a, n);
    printArray(b, n);

    // Free memory
    delete a; 
    delete b; 
    a=NULL;
    b=NULL;

    return 0;
}
