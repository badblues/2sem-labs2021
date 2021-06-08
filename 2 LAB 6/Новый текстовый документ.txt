#include <stdio.h>
#include <malloc.h>

#define tStrSize 40

typedef struct symbolCode symCode;
typedef struct tree tree;

int enterString(char **str_pointer);

tree *makeTree(tree **freqTable, int tableSize);

tree **makeFreqTable(char *string, int size, int *tableSize);

symCode *makeCodeTable(tree* codeTree, int tableSize);

void searchNode(tree node, symCode *codes);

struct symbolCode {
    char symbol;
    char code[10];
    int counter;
};

struct tree {
    char symbols[tStrSize];
    int frequency;
    struct tree *parent;
    struct tree *child0;
    struct tree *child1;
};

int main() {

    char *string;
    int size = enterString(&string);
    char *string2 = malloc(size*sizeof(char));
    for (int i=0; i<=size; i++)
        string2[i]=string[i];
    printf("%s", string);
    printf("\n");

    int tableSize;
    tree **freqTable = makeFreqTable(string, size, &tableSize);
    for (int i = 0; i <= tableSize; i++) {
        printf("%c %d | ", freqTable[i]->symbols[0], freqTable[i]->frequency);
    }
    printf("\n");

    tree *codeTree = makeTree(freqTable, tableSize);
    free(freqTable);

    symCode *codes = makeCodeTable(codeTree, tableSize);
    for (int i=0; i<=tableSize; i++){
        printf("%c ", codes[i].symbol);
        int j=0;
        while (codes[i].code[j]<'2'){
            printf("%c",codes[i].code[j]);
            j++;
        }
        printf("\n");
    }
    for (int i = 0; i<=size; i++){
        for (int j = 0; j<=tableSize; j++)
            if (string2[i]==codes[j].symbol){
                int k=0;
                while(codes[j].code[k] != '2'){
                    printf("%c", codes[j].code[k]);
                    k++;
                }
            }
        printf(" ");
    }
    return 0;
}

int enterString(char **str_pointer) {

    int memSize = 30;
    char c = ' ';
    int i = -1, k = 1;
    *str_pointer = (char *) malloc(memSize * sizeof(char));
    printf("Enter:\n");
    while (1) {
        if (i + 2 == k * memSize) {
            k++;
            (*str_pointer) = (char *) realloc(*str_pointer, k * memSize * sizeof(char));
        }
        scanf("%c", &c);
        if (c == '\n') {
            (*str_pointer)[i + 1] = '\0';
            break;
        }
        i++;
        (*str_pointer)[i] = c;
    }
    int size = i + 1;
    return (size);
}

tree **makeFreqTable(char *string, int size, int *tableSize) {


    tree **freqTable = (tree **) malloc(sizeof(tree *));
    *tableSize = -1;
    while (size > 0) {
        int counter = 1;
        char symbol = string[0];
        int i = 1;
        while (string[i] != '\0') {
            if (string[i] == string[0]) {
                for (int j = i; j <= size - 1; j++) string[j] = string[j + 1];
                counter++;
            } else i++;
        }
        for (int h = 0; h < size; h++) string[h] = string[h + 1];
        (*tableSize)++;
        freqTable = (tree **) realloc(freqTable, (*tableSize + 1) * sizeof(tree *));
        freqTable[*tableSize] = (tree *) malloc(sizeof(tree));
        freqTable[*tableSize]->symbols[0] = symbol;
        freqTable[*tableSize]->symbols[1] = '\0';
        freqTable[*tableSize]->frequency = counter;
        freqTable[*tableSize]->child0 = NULL;
        freqTable[*tableSize]->child1 = NULL;
        size -= counter;
    }
    return (freqTable);
}

tree *makeTree(tree **freqTable, int tableSize) {

    tree *codeTree; //tree's top
    if (tableSize==0) return (freqTable[tableSize]);
    int i = -1;
    while(tableSize >0){
        i++;
        tree *tmp = (tree*)malloc(sizeof(tree));
        int min1 = 1000, min2 = 1000, min_id1=-1, min_id2=-1;
        for (int j = 0; j<=tableSize; j++)
            if (freqTable[j]->frequency<min1){
                min_id1=j;
                min1=freqTable[j]->frequency;
            }
        for (int j = 0; j<=tableSize; j++)
            if ((freqTable[j]->frequency<min2)&&(freqTable[j]!=freqTable[min_id1])){
                min_id2=j;
                min2=freqTable[j]->frequency;
            }
        tmp->frequency=freqTable[min_id1]->frequency+freqTable[min_id2]->frequency;
        tmp->child0=freqTable[min_id1];
        freqTable[min_id1]->parent=tmp;
        tmp->child1=freqTable[min_id2];
        freqTable[min_id2]->parent=tmp;
        int j=0, k=-1;
        while(freqTable[min_id1]->symbols[j]!='\0'){
            tmp->symbols[++k]=freqTable[min_id1]->symbols[j++];
        }
        j=0;
        while(freqTable[min_id2]->symbols[j]!='\0'){
            tmp->symbols[++k]=freqTable[min_id2]->symbols[j++];
        }
        tmp->symbols[++k]='\0';
        freqTable[min_id2]=tmp;
        for (int h = min_id1; h<tableSize; h++) freqTable[h]=freqTable[h+1];
        tableSize--;
        if (tableSize==0)codeTree=tmp;
    }
    return (codeTree);
}

symCode *makeCodeTable(tree* codeTree, int tableSize){

    int i = -1;
    symCode *codes = (symCode *) malloc(sizeof(symCode));
    if (tableSize==0){
        codes[0].symbol=codeTree->symbols[0];
        codes[0].code[0]='0';
        codes[0].code[1]='2';
        return (codes);
    }
    while (tableSize >= 0) {
        i++;
        codes = (symCode *) realloc(codes, (i + 1) * sizeof(symCode));
        codes[i].symbol = 0;
        codes[i].counter = -1;
        searchNode(*codeTree, &codes[i]);
        tableSize--;
    }

    return(codes);
}

void searchNode(tree node, symCode *codes) {

    if (node.child0 != NULL) {
        codes->counter++;
        codes->code[codes->counter] = '0';
        searchNode(*node.child0, codes);
    }
    if (codes->symbol != 0) return;
    if (node.child1 != NULL) {
        codes->counter++;
        codes->code[codes->counter] = '1';
        searchNode(*node.child1, codes);
    }
    if (codes->symbol != 0) return;

    if (node.symbols[1] == '\0'){
        codes->symbol = node.symbols[0];
        codes->code[codes->counter + 1] = '2';
    }
    else
        codes->counter--;
    if ((node.parent->child0!=NULL)&&(node.parent->child0->symbols[0]==node.symbols[0]))
        node.parent->child0 = NULL;
    else if ((node.parent->child1!=NULL)&&(node.parent->child1->symbols[0]==node.symbols[0]))
        node.parent->child1 = NULL;
}