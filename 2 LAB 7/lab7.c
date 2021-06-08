#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define size 10
#define word_size 4

typedef struct List List;

struct List {

    int value;
    char *str;
    struct List *prev;
    struct List *next;

};

void initializeList(List **head,int val, char *str_tmp);

void pushList(List **head, int val, char *str_tmp);

void fillInTheList(void *head);

int compareInt(List *first, List *second);

int compareStr(List *first, List *second);

void bubleSort(void **head, int (*compare)());

void swap(void *q, void *p);

int main() {

    List *head = NULL;
    fillInTheList(&head);
    printf("Unsorted:\n");
    for (List *p = head; p != NULL; p = p->next)
        printf("%d ", p->value);
    printf("\n");
    for (List *p = head; p != NULL; p = p->next) {
        printf(p->str);
        printf(" ");
    }
    bubleSort((void **) &head, compareInt);
    printf("\nSorted by int:\n");
    for (List *p = head; p != NULL; p = p->next) {
        printf("%d ", p->value);
    }
    printf("\nSorted by string:\n");
    bubleSort((void **) &head, compareStr);
    for (List *p = head; p != NULL; p = p->next) {
        printf(p->str);
        printf(" ");
    }
    return 0;
}

void initializeList(List **head,int val, char *str_tmp) {

    List *tmp = (List *) malloc(sizeof(List));
    int i = 0;
    tmp->str = (char *) malloc((word_size+1) * sizeof(char));
    while (str_tmp[i-1] != '\0') {
        tmp->str[i] = str_tmp[i];
        i++;
    }
    tmp->str[i+1] = 0;
    tmp->value = val;
    tmp->next = NULL;
    tmp->prev = NULL;
    *head = tmp;

}

void pushList(List **head, int val, char *str_tmp) {

    List *tmp = (List *) malloc(sizeof(List));
    int i = 0;
    tmp->str = (char *) malloc((word_size+1) * sizeof(char));
    while (str_tmp[i - 1] != '\0') {
        tmp->str[i] = str_tmp[i];
        i++;
    }
    tmp->str[++i] = '\0';
    tmp->value = val;
    tmp->next = *head;
    tmp->prev = (*head)->prev;
    (*head)->prev = tmp;
    *head = tmp;

}

void fillInTheList(void *head) {

    char *str_tmp = (char *) malloc((word_size+1) * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < word_size; i++) str_tmp[i] = rand() % 26 + 97;
    str_tmp[word_size] = '\0';
    initializeList(head, rand() % 100, str_tmp);
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < word_size; j++) str_tmp[j] = rand() % 26 + 97;
        str_tmp[word_size] = '\0';
        pushList(head, rand() % 100, str_tmp);
    }

}

int compareInt(List *first, List *second) {

    if (second->value < first->value) return 1;
    else return 0;
}

int compareStr(List *first, List *second) {

    for (int i = 0; i < word_size; i++){
        if (second->str[i] < first->str[i]) return 1;
        else if (second->str[i] == first->str[i]) continue;
        return 0;
    }
}

void bubleSort(void **head, int (*compare)()) {

    for (int i = 0; i < size; i++) {
        for (List *p = *head; p->next != NULL; p = p->next)
            if (compare(p, p->next)) {
                if (p == *head)
                    *head = p->next;
                swap(p, p->next);
                p = p->prev;
            }
    }
}

void swap(void *q, void *p) {

    List *tmp = (List *) malloc(sizeof(List));
    List *qs;
    List *ps;
    qs = q;
    ps = p;
    if (qs->prev != NULL)
        qs->prev->next = tmp;
    qs->next->prev = tmp;
    tmp->prev = qs->prev;
    tmp->next = qs->next;

    ps->prev->next = qs;
    if (ps->next != NULL)
        ps->next->prev = qs;
    qs->next = ps->next;
    qs->prev = ps->prev;

    if (tmp->prev != NULL)
        tmp->prev->next = ps;
    if (tmp->next != NULL)
        tmp->next->prev = ps;
    ps->prev = tmp->prev;
    ps->next = tmp->next;
}