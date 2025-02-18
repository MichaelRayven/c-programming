#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lshift(char *str, int n) {
    int i, len = strlen(str);
    for (i = 0; i < (len - n); i++) {
        str[i] = str[i + n];
    }
    str[i] = '\0';
}

char *getWord(char *str) {
    char *word = malloc(sizeof(char[20]));
    int j = 0;

    if (word == NULL) {
        perror("Memory allocation error!");
        return NULL;
    }

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            word[j++] = str[i];

            if (str[i + 1] == ' ' || str[i + 1] == '\n' || str[i + 1] == '\0') {
                word[j++] = '\0';
                
                lshift(str, i + 1);

                return word;
            }
        }
    }

    return NULL;
}

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    // Creating a file
    char text[]="Through me you pass into the city of woe:\n"
"Through me you pass into eternal pain:\n"
"Through me among the people lost for aye.\n"
"Justice the founder of my fabric moved:\n"
"To rear me was the task of power divine,\n"
"Supremest wisdom, and primeval love.\n"
"Before me things create were none, save things\n"
"Eternal, and eternal I shall endure.\n"
"All hope abandon, ye who enter here.";

    FILE *inputFile, *outputFile;
    inputFile = fopen("text.txt", "w");
    fputs(text, inputFile);
    fclose(inputFile);

    // Reading from file
    char st[80];
    inputFile = fopen("text.txt", "r");

    int j = 0, n = 0;
    char *word = NULL;
    char **words = malloc(200 * sizeof(char *));
    // char **words = NULL;

    if (words == NULL) {
        perror("Memory allocation error!");
        fclose(inputFile);
        return 1;
    }

    // Get words list
    while (fgets(st, 80, inputFile)) {
        word = getWord(st);
        while (word != NULL) {
            // printf("%d %s\n", strlen(word), word);
            
            // words = realloc(words, (n + 1) * sizeof(char *));
            words[n++] = word;
            word = getWord(st);
        }
    }
    
    words = realloc(words, n * sizeof(char *));
    if (words == NULL) {
        perror("Memory allocation error!");
        fclose(inputFile);
        return 1;
    }

    fclose(inputFile);
    
    qsort(words, n, sizeof(char *), compareStrings);

    // Output words
    outputFile = fopen("text2.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%s\n", words[i]);
    }
    fclose(outputFile);
    
    // Clear memory
    for (int i = 0; i < n; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}