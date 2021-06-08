#include <stdio.h>
#include <malloc.h>
#include <math.h>

int enterString(char **str_pointer);

int *inCode(char *string, int size, int *coded_size);

char *outCode(int *coded, int coded_s);

void getBin(char *tmp, int x);

int main() {
    char *string;
    int size = enterString(&string);
    int coded_size = 0;
    int *coded = inCode(string, size, &coded_size);
    free(string);
    char *string2 = outCode(coded, coded_size);
    printf("\nDecoded string:\n");
    printf("%s", string2);
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

int *inCode(char *string, int size, int *coded_size) {

    int *coded = malloc(sizeof(int));
    printf("Codes (in decimal):\n");
    for (int i = 0; i < size; i++) {
        if ((string[i] >= 65) && (string[i] <= 90) && (string[i + 1] >= 65) && (string[i + 1] <= 90) &&
            (string[i + 2] >= 65) && (string[i + 2] <= 90)) {
            coded = (int *) realloc(coded, (++(*coded_size)) * sizeof(int));
            coded[*coded_size - 1] =
                    ((int) string[i] - 64) * 1024 + ((int) string[i + 1] - 64) * 32 + (int) string[i + 2] - 64 +
                    32768;
            i += 2;
            printf("%d ", coded[*coded_size - 1]);
        } else if ((string[i] >= 65) && (string[i] <= 90) && (string[i + 1] >= 65) && (string[i + 1] <= 90)) {
            coded = (int *) realloc(coded, (++(*coded_size)) * sizeof(int));
            coded[*coded_size - 1] = ((int) string[i] - 64) * 32 + (int) string[i + 1] - 64 + 1024;
            i += 1;
            printf("%d ", coded[*coded_size - 1]);
        } else if ((string[i] >= 65) && (string[i] <= 90)) {
            coded = (int *) realloc(coded, (++(*coded_size)) * sizeof(int));
            coded[*coded_size - 1] = (int) string[i] - 64 + 32;
            printf("%d ", coded[*coded_size - 1]);
        } else if ((string[i] >= 97) && (string[i] <= 122)) {
            coded = (int *) realloc(coded, (++(*coded_size)) * sizeof(int));
            coded[*coded_size - 1] = (int) string[i] - 96;
            printf("%d ", coded[*coded_size - 1]);
        } else if (string[i] == 32) {
            coded = (int *) realloc(coded, (++(*coded_size)) * sizeof(int));
            coded[*coded_size - 1] = 31;
            printf("%d ", coded[*coded_size - 1]);
        }

    }
    printf("\n");
    return (coded);
}

char *outCode(int *coded, int coded_s) {

    int str_s = 0;
    char *string = (char *) malloc(
            10 * sizeof(char));
    char *tmp = (char *) malloc(16 * sizeof(char));
    printf("Codes (in binary):\n");
    for (int i = 0; i < coded_s; i++) {
        getBin(tmp, coded[i]);
        printf("%s ", tmp);
        if (coded[i] > 32768) {
            string = (char *) realloc(string, (++str_s + 2) * sizeof(char));
            string[str_s - 1] = 64;
            for (int k = 1; k <= 5; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 5 - k);
            string[++str_s - 1] = 64;
            for (int k = 6; k <= 10; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 10 - k);
            string[++str_s - 1] = 64;
            for (int k = 11; k <= 15; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 15 - k);
        } else if (coded[i] > 1024) {
            string = (char *) realloc(string, (++str_s + 1) * sizeof(char));
            string[str_s - 1] = 64;
            for (int k = 1; k <= 5; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 5 - k);

            string[++str_s - 1] = 64;
            for (int k = 6; k <= 10; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 10 - k);
        } else if (coded[i] > 32) {
            string = (char *) realloc(string, (++str_s) * sizeof(char));
            string[str_s - 1] = 64;
            for (int k = 1; k <= 5; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, 5 - k);
        } else if (coded[i] == 31) {
            string = (char *) realloc(string, (++str_s + 1) * sizeof(char));
            string[str_s - 1] = ' ';
        } else if (coded[i] > 0 && coded[i] < 31) {
            string = (char *) realloc(string, (++str_s + 1) * sizeof(char));
            string[str_s - 1] = 96;
            int j = -1;
            while (tmp[++j] != '\0');
            j--;
            for (int k = 0; k <= j; k++)
                if (tmp[k] == '1')
                    string[str_s - 1] += pow(2, j - k);
        }
    }
    string[str_s] = '\0';
    return string;
}

void getBin(char *tmp, int x) {

    int tmp_ct = 0;
    while (x > 0) {
        if (x % 2 == 1)
            tmp[++tmp_ct - 1] = '1';
        else
            tmp[++tmp_ct - 1] = '0';
        x /= 2;
    }
    tmp[tmp_ct] = '\0';
    for (int j = 0; j <= (int) (tmp_ct - 2) / 2; j++) {
        char tmpp;
        tmpp = tmp[tmp_ct - 1 - j];
        tmp[tmp_ct - 1 - j] = tmp[j];
        tmp[j] = tmpp;
    }
}