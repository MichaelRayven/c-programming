#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

typedef struct
{
    int number;
    int graduates;
    int universityAdmittions;
    float admissionRate;
} School;

float admissionRate(School *entry) {
    return ((float)entry->universityAdmittions) / entry->graduates * 100;
}

/*
    @param high the last index of the working range
    @param high the first index of the working range
*/
// void quickSort(School arr[], int low, int high) {
//     if (low < high) {
//         int pivot = high;

//         int j = low;
//         for (int i = low; i < high; i++) {
//             if (admissionRate(&arr[i]) < admissionRate(&arr[pivot])) {
//                 School temp = arr[j];
//                 arr[j] = arr[i];
//                 arr[i] = temp;
//                 j++;
//             }
//         }
//         School temp = arr[j];
//         arr[j] = arr[pivot];
//         arr[pivot] = temp;

//         quickSort(arr, j + 1, high);
//         quickSort(arr, low, j - 1);
//     }
// }

int compareFunction(void *schools, const void *a, const void *b) {
    int *indexA = (int *) a;
    int *indexB = (int *) b;
    School *schoolArray = (School *) schools;

    if (schoolArray[*indexA].admissionRate > schoolArray[*indexB].admissionRate) {
        return 1;
    } else {
        return -1;
    }
}

int main() {
    srand(time(NULL));
    School schoolArray[N];
    int indArray[N];

    // Initialize school array
    for (int i = 0; i < N; i++) {
        schoolArray[i].number = 1 + rand() % 150;
        schoolArray[i].graduates = 1 + rand() % 500;
        schoolArray[i].universityAdmittions = rand() % schoolArray[i].graduates;
        schoolArray[i].admissionRate = admissionRate(&schoolArray[i]);
        indArray[i] = i;
    }
    
    qsort_s(indArray, N, sizeof(int), compareFunction, schoolArray);

    // quickSort(schoolArray, 0, N -1);
    
    for (int i = 0; i < N; i++) {
        int idx = indArray[i];
        printf("School %d: Graduates - %d, university admittion rate - %.1f%%\n", 
            schoolArray[idx].number, schoolArray[idx].graduates, admissionRate(&schoolArray[idx]));
    }
}