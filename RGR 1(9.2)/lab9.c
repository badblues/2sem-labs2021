#include <stdio.h>

void print(char *str, ...);

int main() {

    char str[]="kjkf*dsl*d*hfg*";
    printf("Origin: %s\n"
           "insertions: AAA, BBB, CCC, ABOBA\n", str);

    print(str, "AAA", "BBB", "CCC", "ABOBA");
    return 0;
}

void print(char *str, ...){
    char **q=(&str+1);
    while (*str!='\0'){
        if (*str=='*'){
            if (*q!=0){
                printf("%s", *q);
                q++;
                str++;
                continue;
            }
        }
        printf("%c", *str);
        str++;
    }
}
