//Функция получает строку, находит самый внутренний фрагмент в скобках и вырезает его.
//Операция повторяется до тех пор, пока не останется скобок.
//Полученные фрагменты и остаток строки вернуть в динамическом массиве указателей.
//(((((qwe1)(qwe2)pooopa)(looopa)int(char)cuccu)glglglg)zxc)igor(loh)
#include <stdio.h>
#include <malloc.h>

#define BUFF 100

char *enterString(char *str_pointer, int *size);

char **removeBrackets(char *str, char **lines, int *str_size, int *lines_size);

char *findBracket(char *temp, int str_size, int *segment_size, int *segment_start, int *bool);

int main() {

    char *string = (char *) malloc(BUFF * sizeof(char));
    int str_size = BUFF, lines_size;
    string = enterString(string, &str_size);
    char **lines = (char **) malloc(sizeof(char *));
    lines = removeBrackets(string, lines, &str_size, &lines_size);
    free(string);
    for (int i = 0; i <= lines_size; i++) {
        printf(lines[i]);
        printf("\n");
    }
    return 0;
}

char *enterString(char *str_pointer, int *size) {

    char c = ' ';
    int i = -1, k = 1;
    printf("Enter:\n");
    while (1) {
        if (i + 1 == BUFF) {
            k++;
            str_pointer = (char *) realloc(str_pointer, k * BUFF * sizeof(char));
        }
        scanf("%c", &c);
        if (c == '\n') {
            str_pointer[i + 1] = '\0';
            break;
        }
        i++;
        str_pointer[i] = c;
    }
    *size = i + 1;
    return (str_pointer);
}

char **removeBrackets(char *str, char **lines, int *str_size, int *lines_size) {
    int flag = 1;
    *lines_size = -1;
    lines = (char **) malloc(sizeof(char *));
    while (flag) {
        int segment_start = 0;
        int segment_size = 0;
        char *tmp = findBracket(str, *str_size, &segment_size, &segment_start, &flag);
        if (tmp != NULL) {
            (*lines_size)++;
            lines = (char **) realloc(lines, (*lines_size + 1) * sizeof(char *));
            lines[*lines_size] = (char *) malloc((segment_size) * sizeof(char));
            for (int i = 0; i < segment_size; i++) {
                lines[*lines_size][i] = tmp[i];
            }
            lines[*lines_size][segment_size] = '\0';
            for (int i = 0; i < (*str_size - segment_start - segment_size); i++) {
                str[i + segment_start - 1] = str[i + (segment_start) + segment_size + 1];
            }
            *str_size -= segment_size + 2;
        }
    }
    if (*str_size != 0) {
        (*lines_size)++;
        lines = (char **) realloc(lines, (*lines_size + 1) * sizeof(char *));
        lines[*lines_size] = (char *) malloc(*str_size * sizeof(char));
        for (int i = 0; i < *str_size; i++)
            lines[*lines_size][i] = str[i];
        lines[*lines_size][*str_size] = '\0';
    }
    return (lines);
}

char *findBracket(char *temp, int str_size, int *segment_size, int *segment_start, int *bool) {

    *bool = 0;
    int flag = 0, error_flag = 0;
    int lbc = 0, rbc = 0, counter = 0;
    for (int i = 0; i < str_size; i++) {
        if (temp[i] == '(') {
            lbc++;
            if (lbc - rbc > counter) {
                counter = lbc - rbc;
                flag = 1;
                *bool = 1;
                *segment_size = -1;
                *segment_start = i + 1;
            }
        }
        if (temp[i] == ')') {
            rbc++;
            if (flag == 1) flag = 0;
        }
        if (flag == 1) (*segment_size)++;
        if (rbc > lbc) error_flag = 1;  //ERROR
    }
    if ((lbc != rbc) && (lbc != 0)) error_flag = 1;  //ERROR
    if (error_flag) {
        printf("\nAmount of start and end brackets are not equal\n");
        *bool = 0;
        return (NULL);
    }
    if (*bool != 0) return (&temp[*segment_start]);
    else return (NULL);
}