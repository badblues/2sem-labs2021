//Заменить в строке все повторяющиеся символы на цифру и символ
#include <stdio.h>
#include <malloc.h>

int enterString (char* q);
char *findDuplicates (char *str, int *sz, int *ct);
void deleteDuplicates (int *sz, char *start, int *delSize);



int main(){

    char *string = (char*)malloc(sizeof(char));
    int dSize=0;
    char *bg=string;
    int size = enterString(string);
    while (bg!=NULL){
        bg= findDuplicates(string, &size, &dSize);
        deleteDuplicates(&size, bg, &dSize);
    }
    printf(string);

    return 0;
}

int enterString (char* q){


    char c = ' ';
    int i = -1;
    printf("Enter:\n");
    while (1){
        scanf("%c", &c);
        if (c=='\n'){
            q = (char*)realloc(q, (i+2)*sizeof(char));
            q[i+1]='\0';
            break;
        }
        i++;
        q = (char*)realloc(q, (i+1)*sizeof(char));
        q[i] = c;
    }
    return (i+1);
}

char *findDuplicates(char *str, int *sz, int *ct){

    int i=0; *ct=1;
    while (1){
        if(i==*sz) return (NULL); //If we crossed a string we return empty pointer
        int j=i, flag=0;
        if (!((str[j]>=48)&&(str[j]<=57)))
            while (str[j]==str[j+1]){
            (*ct)++; j++; flag=1;
            }
        if (flag==1)
            return(str+i);
        i++;
    }
}

void deleteDuplicates (int *sz, char *start, int *delSize){

    if (start==NULL) return;
    int kept_s=1;
    int k=*delSize;
    while (k%10!=0){
        kept_s++;
        k/=10;
    }
    int i=kept_s-2;
    k=*delSize;
    while (i>=0){
        *(start+i)=k%10+'0';
        i--; k/=10;
    }
    *sz-=(*delSize-kept_s);
    int j=2;
    while (1){
        if ((*delSize==0)||(start[j+*delSize-kept_s-1]=='\0')) break;  //break happens when we move '\0'
        start[j]=start[j+(*delSize-kept_s)];
        j++;
    }
}