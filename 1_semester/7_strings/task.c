#include <stdio.h>
#include <string.h>

int main()
{
    // В заданном предложении найти слово, в котором количество буквы 'а' максимальна. Вывести найденное слово и посчитать, сколько раз буква 'а' встречается в этом слове.


    char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int max = 0, maxInd = -1, current = 0, currentInd = -1;

    // Count the occurrances of letter 'a' in a string, reset the count when str[i] == ' '
    // Save the maximum count and the index of the beggining of the word
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            if (current > max)
            {
                // Save max
                max = current;
                maxInd = currentInd;
            }
            // Reset
            current = 0;
            currentInd = i;
        }
        // Increment count if we find the letter 'a'
        else if (str[i] == 'a' || str[i] == 'A')
        {
            current++;
        }
    }
    printf("Found word: ");

    // Print out the word letter by letter
    // Because I don't know how to get a substring
    for (int i = maxInd + 1; i < strlen(str); i++)
    {
        if (str[i] == ' ')
        {
            break;
        }
        printf("%c", str[i]);
    }

    // Print out saved max count
    printf(" with %d occurrances of letter 'a'", max);
}