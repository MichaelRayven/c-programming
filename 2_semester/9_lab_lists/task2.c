#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    void *data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

typedef struct StudentGrades {
    char surname[20];
    char grades[4];
} StudentGrades;

void printList(LinkedList *list, void (*printFunc)(void *)) {
    Node *p = list->head;
    while (p != NULL) {
        printFunc(p->data);
        p = p->next;
    }
}

void printStudentGrade(void *data) {
    StudentGrades *g = (StudentGrades *) data;
    printf("%s: Grades - %d, %d, %d, %d\n", 
            g->surname, g->grades[0], g->grades[1], g->grades[2], g->grades[3]);
}

void deleteNode(LinkedList *list, Node *n) {
    Node *prev = n->prev;
    Node *next = n->next;

    if (list->head == n) {
        list->head = next;
        next->prev = prev;
    } else if (list->tail == n) {
        list->tail = prev;
        prev->next = next;
    } else {
        prev->next = next;
        next->prev = prev;
    }

    free(n);
}

void sortLinkedList(LinkedList *list, int (*compareFunc)(void *, void *)) {
    Node *ptr, *next, *prev;
    int flag = 0;

    do {
        ptr = list->head;
        prev = list->head;
        flag = 0;

        while(ptr->next != NULL) {
            next = ptr->next;
            
            if (compareFunc(ptr->data, next->data)) {
                flag = 1;

                if (ptr == list->head) {
                    ptr->next = next->next;
                    next->next = ptr;
                    prev = next;
                    list->head = next;
                } else {
                    ptr->next = next->next;
                    next->next = ptr;
                    prev->next = next;
                    prev = next;
                }

                continue;
            }

            prev = ptr;
            ptr = ptr->next;
        }
    } while(flag);
}

int compareStudentGrades(void *a, void *b) {
    StudentGrades *g1 = (StudentGrades *) a;
    StudentGrades *g2 = (StudentGrades *) b;
    return strcmp(g1->surname, g2->surname) > 0;
}

int main() {
    StudentGrades data[] = {
        {"Jones", {1, 2, 3, 4}},
        {"Smith", {5, 5, 5, 5}},
        {"Wilson", {4, 5, 5, 4}},
        {"Miller", {1, 3, 3, 4}},
        {"Garcia", {2, 5, 3, 4}},
    };
    int size = (int) sizeof(data) / sizeof(data[0]);

    LinkedList list = {NULL, NULL};
    Node *n;
    for (int i = 0; i < size; i++) {
        n = malloc(sizeof(Node));
        n->data = &data[i];
        n->next = NULL;
        n->prev = NULL;
        
        if (list.head == NULL) {
            list.head = n;
            list.tail = n;
        } else {
            list.tail->next = n;
            n->prev = list.tail;
            list.tail = n;
        }
    }

    // Sort linked list
    // sortLinkedList(&list, compareStudentGrades);
    
    // Print linked list
    printList(&list, printStudentGrade);

    Node *p = list.head;
    while (p != NULL) {
        StudentGrades *sg = (StudentGrades *) p->data;

        Node *next = p->next;
        if (sg->grades[0] <= 2 || sg->grades[1] <= 2 || 
            sg->grades[2] <= 2 || sg->grades[3] <= 2) {
            deleteNode(&list, p);
        }
        p = next;
    }
    
    // Print linked list
    printf("\nCleaned list:\n");
    printList(&list, printStudentGrade);
    
    // Deallocate linked list
    p = list.head;
    while (p != NULL) {
        Node *temp = p;
        p = p->next;
        free(temp);
    }

    return 0;
}