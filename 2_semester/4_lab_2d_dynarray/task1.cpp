#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 5;
// typedef int rown[n];

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

    int m = 0;
    printf("Please enter the number of rows: ");
    readInt(&m);

    int(*b)[n] = new int[m][n];
    int(*c)[n - 1] = new int[m - 1][n - 1];

    if (b == NULL || c == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    int maxI = 0, maxJ = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = rand() % (100 + 1);
            if (b[i][j] > b[maxI][maxJ]) {
                maxI = i;
                maxJ = j;
            }
        }
    }

    for (int i = 0, k = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != maxI && j != maxJ) {
                c[k / (n - 1)][k % (n - 1)] = b[i][j];
                k++;
            }
        }
    }

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

    delete b;
    delete c;

    return 0;
}