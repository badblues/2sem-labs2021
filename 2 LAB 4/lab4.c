#include <stdio.h>
#include <malloc.h>
#include <time.h>

struct element {
    int value;
    struct element *next;
    struct element *prev;
};

typedef struct element elem;

void initialize(elem **head, int val);

void push(elem **head, int val);

int fillInTheList(elem **head);

void swapElements(elem **head, int f_id, int s_id);

void selectionSort(elem **head, int sz);

int main() {

    elem *head = NULL;
    int size = fillInTheList(&head);
    selectionSort(&head, size);
    elem *tmp = head;
    printf("\n");
    for (int i=0; i < size; i++){
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    return 0;
}

void initialize(elem **head, int val) {

    elem *tmp;
    tmp = (elem *) malloc(sizeof(elem));
    tmp->value = val;
    tmp->next = tmp;
    tmp->prev = tmp;
    *head = tmp;

}

void push(elem **head, int val) {

    elem *tmp = (elem *) malloc(sizeof(elem));
    tmp->value = val;
    tmp->next = *head;
    tmp->prev = (*head)->prev;
    (*head)->prev->next = tmp;
    (*head)->prev = tmp;
    *head = tmp;
}

int fillInTheList(elem **head) {

    int sz = 10;
    srand(time(NULL));
    initialize(head, rand()%100);
    for (int i = 0; i < sz - 1; i++) {
        push(head, rand()%100);
    }
    printf("%d ", (*head)->value);
    for (elem *p = (*head)->next; p != *head; p = p->next)
        printf("%d ", p->value);
    return (sz);

}

void swapElements(elem **head, int f_id, int s_id) {

    if (f_id==s_id) return;
    elem *first, *second;
    second = (*head)->prev;
    first = (*head)->prev;
    for (int i = 0; i <= f_id; i++)
        first = first->next;
    for (int i = 0; i <= s_id; i++)
        second = second->next;
    elem *tmp;
    tmp = (elem *) malloc(sizeof(elem));

    first->prev->next = tmp;
    first->next->prev = tmp;
    tmp->prev = first->prev;
    tmp->next = first->next;

    second->prev->next = first;
    second->next->prev = first;
    first->next = second->next;
    first->prev = second->prev;

    tmp->prev->next = second;
    tmp->next->prev = second;
    second->prev = tmp->prev;
    second->next = tmp->next;
    if (f_id == 0) *head = second;
}

void selectionSort(elem **head, int sz) {

    if ((*head)==NULL) return;
    int min, min_id = 0;
    elem *ptr;
    for (int i = 0; i < sz; i++) {
        ptr = *head; min=101;
        for (int k = 0; k < i; k++) ptr = ptr->next;
        for (int j = i; j < sz; j++) {
            if (ptr->value < min) {
                min_id = j;
                min = ptr->value;
            }
            ptr = ptr->next;
        }
        swapElements(head, i, min_id);
    }
}