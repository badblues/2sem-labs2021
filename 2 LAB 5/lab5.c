#include <stdio.h>
#include <malloc.h>
#include <time.h>

#define size 5

void createMatrix(int ***matrix);

int **colorMap(int **matrix, int *c_line_ct);

void checkNode(int i, int **tmp, int *colored, int **matrix, int flag);

int main() {

    int **matrix;
    createMatrix(&matrix);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
    int c_line_ct = -1, j; //color counter
    int **colors = colorMap(matrix, &c_line_ct);
    for (int i = 0; i <= c_line_ct; i++) {
        j = 0;
        while (colors[i][j] < size + 1) {
            printf("%d ", colors[i][j] + 1);
            j++;
        }
        printf("\n");
    }
    return 0;
}

void createMatrix(int ***matrix) {

    (*matrix) = (int **) malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        (*matrix)[i] = (int *) malloc(size * sizeof(int));
    srand(time((NULL)));
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++)
            if (i == j) {
                (*matrix)[i][j] = 0;
            } else {
                (*matrix)[i][j] = rand() % 2;
                (*matrix)[j][i] = (*matrix)[i][j];
            }
}

int **colorMap(int **matrix, int *c_line_ct) {

    //Color matrix:
    int **colors = (int **) malloc(sizeof(int *));
    //Temporary array, which elements describe if we can unite nodes or not
    int *tmp = (int *) malloc(size * sizeof(int));
    //Temporary array with elements already united
    int *colored = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)colored[i] = 0;

    for (int i = 0; i < size; i++) {
        if (colored[i]) continue;
        for (int k = 0; k < size; k++) tmp[k] = 1;
        tmp[i] = 0;
        checkNode(i, &tmp, colored, matrix, 1);
        int tmp_sum = 1;
        for (int k = 0; k < size; k++) tmp_sum+=tmp[k];
        (*c_line_ct)++;
        int c_ct2 = 0;
        colored[i] = 1;
        colors = (int **) realloc(colors, (*c_line_ct + 1) * sizeof(int *));
        colors[*c_line_ct] = (int *) malloc((tmp_sum + 1) * sizeof(int));
        colors[*c_line_ct][c_ct2] = i;
        for (int h = 0; h < size; h++) {
            if (colored[h]) continue;
            if (tmp[h] == 1) {
                colored[h] = 1;
                colors[*c_line_ct][++c_ct2] = h;
            }
        }
        colors[*c_line_ct][c_ct2 + 1] = size + 1;
    }
    return (colors);
}

void checkNode(int i, int **tmp, int *colored, int **matrix, int flag) {

    for (int k = 0; k < size; k++) if (colored[k] == 1) (*tmp)[k] = 0;
    int bool = flag;
    int tmp_sum = 0;
    for (int j = i; j < size; j++)
        if (matrix[i][j] == 1) (*tmp)[j] = 0;
    for (int j = i; j < size; j++) tmp_sum += (*tmp)[j];
    if ((tmp_sum == 0) || (tmp_sum == 1)) {
        bool = 0;
    }
    if (bool)
        for (int j = i + 1; j < size; j++)
            if (((*tmp)[j]) && (j > i)) checkNode(j, tmp, colored, matrix, bool);
}