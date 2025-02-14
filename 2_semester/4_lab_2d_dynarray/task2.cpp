#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readInt(int *number)
{
    char line[64];
    fgets(line, sizeof(line), stdin);

    if (sscanf(line, "%d", number) != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int **createMatrix(int m, int n) {
    int **a = new int *[m];

    if (a == NULL) {
        printf("Memory allocation failed");
        return NULL;
    } else {
        for (int i = 0; i < m; i++) {
            a[i] = new int[n];

            if (a[i] == NULL) {
                printf("Memory allocation failed");
                return NULL;
            }
        }
    }
    return a;
}

void destroy2dArray(int **arr, int m) {
    for (int i = 0; i < m; i++) {
        delete arr[i];
    }
    delete arr;
}

int main()
{
    srand(time(NULL));
    int m = 0, n = 0;

    printf("Please enter the number of rows: ");
    readInt(&m);
    printf("Please enter the number of columns: ");
    readInt(&n);

    // Allocate memory
    int **a = createMatrix(m, n);
    int **d = createMatrix(m + 1, n + 1);

    // Fill the array a and d
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i][j] = rand() % (100 + 1);
            d[i][j] = a[i][j];
        }
    }

    // Fill the extra rows and columns in d with zeroes
    for (int i = 0; i < m; i++) {
        d[i][n] = 0;
    }
    for (int j = 0; j <= n; j++) {
        d[m][j] = 0;
    }

    // Calculate the sums
    for (int i = 0; i < m; i++)
    {   
        for (int j = 0; j < n; j++)
        {
            d[m][n] += a[i][j];
            d[i][n] += a[i][j];
            d[m][j] += a[i][j];
        }
    }

    // Print results
    printf("Initial array:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
    printf("\nSum array:\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    // Deallocate memeory
    destroy2dArray(a, m);
    destroy2dArray(d, m + 1);

    return 0;
}