#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int room;
    float area;
    char faculty[20];
    int residents;
} DormitoryRoom;

int main() {
    DormitoryRoom a[] = {
        {400, 16.0f, "IVT", 1},
        {401, 32.0f, "MPM", 3},
        {402, 24.0f, "MPM", 2},
        {403, 18.0f, "IVT", 2},
        {404, 10.0f, "IEF", 1},
        {405, 40.0f, "AES", 6},
        {406, 42.0f, "IVT", 5},
        {407, 12.0f, "AES", 1},
    };
    int size = ((int)sizeof(a) / sizeof(a[0]));

    // Create and initialize faculties array with empty strings
    int facultyCount = 0;
    char **faculties = (char**) malloc(sizeof(char *) * size);

    if (faculties == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } else {
        for (int i = 0; i < size; i++) {
            faculties[i] = "";
        }
    }

    // Make a list of all unique faculty names
    for (int i = 0; i < size; i++) {
        short found = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(a[i].faculty, faculties[j]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faculties[facultyCount] = a[i].faculty;
            facultyCount++;
        }
    }

    // Get statistics for each faculty in the list
    for (int i = 0; i < facultyCount; i++) {
        float area = 0;
        int roomCnt = 0;
        int students = 0;
        
        for (int j = 0; j < size; j++) {
            if (strcmp(a[j].faculty, faculties[i]) == 0) {
                area += a[j].area;
                students += a[j].residents;
                roomCnt++;
            }
        }

        printf("%s faculty: rooms - %d, students - %d, average area per student - %.2f\n", faculties[i], roomCnt, students, area / students);
    }

    return 0;
}