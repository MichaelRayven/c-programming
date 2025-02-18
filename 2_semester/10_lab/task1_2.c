#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    // Creating a file
    FILE *inputFile, *outputFile;
    char text[]="Through me you pass into the city of woe:\n"
"Through me you pass into eternal pain:\n"
"Through me among the people lost for aye.\n"
"Justice the founder of my fabric moved:\n"
"To rear me was the task of power divine,\n"
"Supremest wisdom, and primeval love.\n"
"Before me things create were none, save things\n"
"Eternal, and eternal I shall endure.\n"
"All hope abandon, ye who enter here.";

    inputFile = fopen("text.txt", "w");
    fputs(text, inputFile);
    fclose(inputFile);

    // Reading from file
    char word[20];
    inputFile = fopen("text.txt", "r");

    int n = 0;
    char **words = NULL;

    // Get words list
    while (fscanf(inputFile, "%s", &word) == 1) {
        if (word != NULL) {
            words = realloc(words, (n + 1) * sizeof(char *));
            words[n] = malloc(sizeof(char[20]));

            if (words == NULL || words[n] == NULL) {
                perror("Memory allocation error!");
                fclose(inputFile);
                return 1;
            }

            strcpy(words[n++], word);
        }
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