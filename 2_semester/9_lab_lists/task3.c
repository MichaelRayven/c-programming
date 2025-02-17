#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char surname[20];
    int g1, g2, g3, g4;
} student;

typedef struct tree {
    void *key;
    struct tree *l, *r;
} tree;

void add(tree *(*t), void *data, int (*cmpfunc)(void *, void *)) {
    if ((*t) == NULL) {
        (*t) = malloc(sizeof(tree)); 
        (*t)->key = data;
        (*t)->l = (*t)->r = NULL;
        return;
    }
    if ( cmpfunc(data, (*t)->key) < 0 )
        add( &((*t)->l), data, cmpfunc );
    else 
        add ( &((*t)->r), data, cmpfunc );
}

void print_ltr(tree *t){
    if ( !t ) return; 
    print_ltr(t->l); 
    student *s = (student *) t->key;
    printf("%s ", s->surname); 
    print_ltr(t->r); 
}

void print_rtl(tree *t){
    if ( !t ) return; 
    print_rtl(t->r); 
    student *s = (student *) t->key;
    printf("%s ", s->surname); 
    print_rtl(t->l); 
}

tree * search(tree * t, void *x, int (*cmpfunc)(void *, void *)) {
    if ( ! t ) 
        return NULL; 
    if ( cmpfunc(x, t->key) == 0 ) 
        return t; 
    if ( cmpfunc(x, t->key) < 0 ) 
        return search ( t->l, x, cmpfunc );
    return search ( t->r, x, cmpfunc );
}

int studentcmp(void *a, void *b) {
    student *g1 = (student *) a;
    student *g2 = (student *) b;
    return strcmp(g1->surname, g2->surname);
}

int surnamecmp(void *a, void *b) {
    char *g1 = (char *) a;
    student *g2 = (student *) b;
    
    // printf("[%s %s] %d\n", g1, g2->surname, strcmp(g1, g2->surname));
    return strcmp(g1, g2->surname);
}

void studentprint(void *data) {
    student *g = (student *) data;
    printf("%s: Grades - %d, %d, %d, %d\n", 
            g->surname, g->g1, g->g2, g->g3, g->g4);
}

int main() {
    student data[] = {
        {"Jones", 1, 2, 3, 4},
        {"Smith", 5, 5, 5, 5},
        {"Wilson", 4, 5, 5, 4},
        {"Miller", 1, 3, 3, 4},
        {"Garcia", 2, 5, 3, 4},
    };
    int size = (int) sizeof(data) / sizeof(data[0]);

    // Initialize tree
    tree *t = NULL;
    for (int i = 0; i < size; i++) {
        add(&t, &data[i], studentcmp);
    }

    printf("Surnames in ascending order: \n");
    print_ltr(t);
    printf("\n\nSurnames in descending order: \n");
    print_rtl(t);
    printf("\n");

    char line[20];
    do {
        printf("\nEnter a surname to find: ");
        scanf("%s", line);

        tree *t1 = search(t, line, surnamecmp);
        studentprint(t1->key);
    } while (strcmp("end", line) != 0);
}