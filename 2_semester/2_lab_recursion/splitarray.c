#include <stdio.h>
#include <stdio.h>

int readInt(int *number) {
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1) {
        return 0;
    } else {
        return 1;
    }
}

void splitarray(int array[], int n, int i) {
    if (i >= n) {
        return;
    }
    
    if (array[i] < 0) {
        printf("%d ", array[i]);
    }

    splitarray(array, n, i + 1);
    
    if (array[i] > 0) {
        printf("%d ", array[i]);
    }
}

void main() {
    int array[8] = {123, -123, 112, 12333, -1239, 1, -2, 5};
    int length = (int) sizeof(array)/sizeof(array[0]);
    splitarray(array, length, 0);
}