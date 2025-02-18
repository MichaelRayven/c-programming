#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char *fname = "file1.dat";

typedef struct luggage {
    char fullname[32];
    int seats;
    float weight;
} luggage;

void input(char *name); // создание нового файла
void print(char *name); // просмотр файла
void append(char *name); // добавление в файл
void edit(char *name); // поиск и изменение
void delete(char *name); // поиск и удаление

int main() {
    // fread, fwrite, fscanf, fprintf, fseek, ftell
    // SEEK_SET или 0 - начало файла;  
    // SEEK_CUR или 1 – текущая позиция в файле;  
    // SEEK_END или 2 – конец файла. 

    char c;
    while(1) {
        system("CLS");
        puts("  1 - create new file");
        puts("  2 - open file");
        puts("  3 - append to file");
        puts("  4 - search and edit");
        puts("  5 - search and delete");
        puts("  0 - exit");
        
        c = getch();

        switch(c) { 
            case '1':
                input(fname);
                break;
            case '2':
                print(fname);
                break;
            case '3':
                append(fname);
                break;
            case '4':
                edit(fname);
                break;
            case '5':
                delete(fname);
                break;
            case '0':
                return 0;
            default : 
                puts("Wrong mode");
        }

    }

    return 0;
}

void input(char *fname) {
    FILE *f;
    luggage l1;
    char ch;
    f = fopen(fname, "wb");

    system("CLS"); // Clear screen

    printf("Create luggage\n");
    do {
        printf("Passanger's name: ");
        scanf("%s", &l1.fullname);
        printf("Luggage seats: ");
        scanf("%d", &l1.seats);
        printf("Luggage weight: ");
        scanf("%f", &l1.weight);

        fwrite(&l1, sizeof(l1), 1, f);

        printf("\nFinish (y/n)?\n\n");
        ch = getch();
    } while (ch != 'y');

    fclose(f);
}

void print(char *fname) {
    FILE *f;
    luggage l1;
    int i = 1;
    f = fopen(fname, "rb");

    system("CLS"); // Clear screen
    while(fread(&l1, sizeof(l1), 1, f)) {
        printf("Entry - %d\n"
            "Passanger's name: %s\n"
            "Luggage seats: %d\n"
            "Luggage weight: %.3f\n\n", 
        i++, l1.fullname, l1.seats, l1.weight);
    }

    fclose(f);
    getch();
}

void append(char *fname) {
    FILE *f;
    luggage l1;
    char ch;
    f = fopen(fname, "ab");

    system("CLS"); // Clear screen

    printf("Create luggage\n");
    do {
        printf("Passanger's name: ");
        scanf("%s", &l1.fullname);
        printf("Luggage seats: ");
        scanf("%d", &l1.seats);
        printf("Luggage weight: ");
        scanf("%f", &l1.weight);

        fwrite(&l1, sizeof(luggage), 1, f);

        printf("\nFinish (y/n)?\n\n");
        ch = getch();
    } while (ch != 'y');

    fclose(f);
}

void edit(char *fname) {
    FILE *f;
    luggage l1;
    char line[32], ch;
    f = fopen(fname, "rb+");

    system("CLS"); // Clear screen

    printf("Enter passangers name: ");
    scanf("%s", line);

    while (fread(&l1, sizeof(l1), 1, f)) {
        if (strcmp(l1.fullname, line) == 0) {
            printf("Do you want to edit the following entry (y/n)?\n\n");
            printf("Passanger's name: %s\n"
                "Luggage seats: %d\n"
                "Luggage weight: %.3f\n\n", 
            l1.fullname, l1.seats, l1.weight);

            ch = getch();

            if (ch == 'y') {
                printf("Luggage seats: ");
                scanf("%d", &l1.seats);

                printf("Luggage weight: ");
                scanf("%f", &l1.weight);

                // Overwrite
                fseek(f, -sizeof(l1), 1);
                fwrite(&l1, sizeof(l1), 1, f);
                fflush(f); // !!! Clear the buffer
                break;
            }
        }
    }

    fclose(f);
}

void delete(char *fname) {
    FILE *f, *t;
    luggage l1;
    char line[32], ch;
    f = fopen(fname, "rb");
    t = fopen("temp.dat", "wb");

    system("CLS"); // Clear screen

    printf("Enter passangers name: ");
    scanf("%s", line);

    int flag = 0;
    while (fread(&l1, sizeof(l1), 1, f)) {
        if (strcmp(l1.fullname, line) == 0) {
            printf("Do you want to delete the following entry (y/n)?\n\n");
            printf("Passanger's name: %s\n"
                "Luggage seats: %d\n"
                "Luggage weight: %.3f\n\n", 
            l1.fullname, l1.seats, l1.weight);

            ch = getch();

            if (ch == 'y') {
                flag = 1;
            } else {
                break;
            }
        } else {
            fwrite(&l1, sizeof(l1), 1, t);
        }
    }
    
    fclose(f);
    fclose(t);
    
    if (flag) {
        f = fopen(fname, "wb");
        t = fopen("temp.dat", "rb");
        fseek(t, 0, 0);
        
        while(fread(&l1, sizeof(l1), 1, t)) {
            fwrite(&l1, sizeof(l1), 1, f);
        }
        
        fclose(f);
        fclose(t);
    }

    remove("temp.dat");
}