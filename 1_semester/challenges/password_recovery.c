#include <stdio.h>
#include <string.h>
#include <math.h>

int readint(char *message, int *ptr)
{
    printf("%s", message);

    // Drain stdin line into a buffer
    // Scanf doesn't drain stdin buffer if it doesn't fit the format
    char line[64];
    fgets(line, sizeof(line), stdin);

    // Make sure that variables are assigned
    if (sscanf(line, "%d", ptr) != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int readstr(char *message, char *ptr)
{
    printf("%s", message);

    // Drain stdin line into a buffer
    // Scanf doesn't drain stdin buffer if it doesn't fit the format
    char line[64];
    fgets(line, sizeof(line), stdin);

    // Make sure that variables are assigned
    if (sscanf(line, "%s", ptr) != 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int instr(char *str, char chr) {
    for (int i = 0; i < strlen(str); i++) {
        if (chr == str[i]){
            return 1;
        }
    }
    return 0;
}

int main()
{
    char inputs[(int)(2 * pow(10, 5))];
    readstr("Ввод за последнее время: ", inputs);

    char requirements[(int)(2 * pow(10, 5))];
    readstr("Введите требования к паролю: ", requirements);

    int pass_length = 0, pass_min_length = strlen(requirements);
    readint("Введите длину пароля: ", &pass_length);



    int left = 0;
    int right = strlen(requirements);

    if (right >= strlen(inputs)) {
        printf("-1\n");
        return 0;
    }

    int bounds[2] = {left, right};



    while (right <= pass_length) {
        int req_met = 1;
        for (int j = 0; j < pass_min_length; j++) {
            int success = 0;
            for (int i = left; i < right; i++) {
                if (requirements[j] == inputs[i]) {
                    success = 1;
                    break;
                }
            }
            req_met = req_met & success;
        }
        
        if (req_met) {
            bounds[0] = left;
            bounds[1] = right;
        } else {
            if (right - left > pass_min_length) {
                left++;
            } else {
                right++;
            }
        }
    }

    printf("%d, %d\n", bounds[0], bounds[1]);

    return 0;
}