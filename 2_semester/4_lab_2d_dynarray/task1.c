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

int main()
{
    srand(time(NULL));
    int m = 0, n = 5;

    printf("Please enter the number of rows: ");
    readInt(&m);

    // Allocate memory
    int **b = malloc(sizeof(int*) * m);
    int **c = malloc(sizeof(int*) * (m - 1));

    if (b == NULL || c == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    // Find max number's row and column
    // and fill the array b
    int maxI = 0, maxJ = 0;
    for (int i = 0; i < m; i++)
    {
        b[i] = (int *) malloc(sizeof(int) * n);

        if (b[i] == NULL) {
            printf("Memory allocation failed");
            return 1;
        }

        for (int j = 0; j < n; j++)
        {
            b[i][j] = rand() % (100 + 1);
            if (b[i][j] > b[maxI][maxJ]) {
                maxI = i;
                maxJ = j;
            }
        }
    }

    // Fill the array c skipping
    // max number's row and column
    for (int i = 0, k = 0; i < m; i++)
    {   
        if (i != (m - 1)) {
            c[i] = (int *) malloc(sizeof(int) * (n - 1));
        } 
        
        for (int j = 0; j < n; j++)
        {
            if (i != maxI && j != maxJ) {
                c[k / (n - 1)][k % (n - 1)] = b[i][j];
                k++;
            }
        }
    }

    // Print results
    printf("Initial array:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    
    printf("\nMax element is %d b[%d, %d]\n", b[maxI][maxJ], maxI, maxJ);
    printf("Trimmed array:\n");
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    // Deallocate memeory
    for (int i = 0; i < m; i++) {
        free(b[i]);
        if (i != (m - 1)) {
            free(c[i]);
        } 
    }
    free(b);
    b = NULL;
    free(c);
    c = NULL;

    return 0;
}