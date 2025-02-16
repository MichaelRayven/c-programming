#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000
#define MIN 0

void swap(int* a, int* b);

int partition(int arr[], int low, int high) {
    
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void randomFill(int arr[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    }
}

int linearSearch(int arr[], int size, int x) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == x) {
            printf("The number of iterations in linear search: %d\n", i + 1);
            return i;
        }
    } 

    return -1;
}

int binarySearch(int arr[], int size, int x) {
    int L = 0, R = size - 1;
    int i = 0;

    while (L <= R) {
        int M = (L + R) / 2;
        
        if (arr[M] == x) {
            printf("The number of iterations in binary search: %d\n", i + 1);
            return M;
        } else if (arr[M] < x) {
            R = M - 1;
        } else {
            L = M + 1;
        }

        i++;
    }

    return -1;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%03d ", arr[i]);
    }
    printf("\n");
}

int readInt(int *number){
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int arrA[100], arrB[1000], x = -1;

    // Initialize arrays
    randomFill(arrA, 100);
    randomFill(arrB, 1000);

    printf("Initial array: \n");
    printArray(arrB, 1000);

    quickSort(arrA, 0, 100 - 1);
    quickSort(arrB, 0, 1000 - 1);

    printf("\nSorted array: \n");
    printArray(arrB, 1000);
    

    while(1) {
        while(1) {
            printf("\nPlease select a number to search for (-1 to exit): ");
            if (readInt(&x) == 0) {
                printf("Please try again!");
            } else {
                break;
            }
        }

        if (x == -1) break;

        int lAnswer = linearSearch(arrB, 1000, x);
        if (lAnswer != -1) {
            printf("Linear search found number %d at arr[%d]\n", x, lAnswer);
        } else {
            printf("Linear search failed!\n");
        }

        int bAnswer = binarySearch(arrB, 1000, x);
        if (bAnswer != -1) {
            printf("Binary search found number %d at arr[%d]\n", x, bAnswer);
        } else {
            printf("Binary search failed!\n");
        }
    }
    
    return 0;

    // int **arr, int arr[][N][M], int (*a)[]
    // int *a[10] - is a size 10 array of pointers to int 
    // int (*a)[10] - is a pointer to int arrays of size 10 
}
