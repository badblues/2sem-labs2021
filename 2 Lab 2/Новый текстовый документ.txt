#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

struct phone_list {
    long long int ph_num;
    int dd, mm, yy;
    float dur;
    int city_code;
};

typedef struct phone_list List;

List* addRecord(List *tmpp, int *f_id);
void editRecord(List *tmp, int q);
void deleteRecord(List *tmp, int q, int *f_id);
void displayRecord(List *out, int *o_id);
void sortList(int p, List *tmp, int *f_id);
void searchInList(int p, List *tmp, int *f_id);
void calculateInList(int p, List *tmp, int *f_id);
List* fileImport(int *f_id);
void fileExport(List *tmp, int *f_id);

int main() {

    List *table;
    int id = -1; //variable for identification with which record we working now
    table=(List*)malloc(sizeof(List));

    int choice, flag = 1;
    while (flag) {
        printf("-----------------------------------------\n");
        printf("Choose option:\n1.Add a record\n2.Display records\n3.Import records\n4.Export records\n");
        printf("5.Edit record\n6.Delete record\n7.Sort\n8.Search in record\n9.Calculate\n10.Exit\n");
        printf("-----------------------------------------\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                table=addRecord(table, &id);
                break;
            case 2:
                if (id==-1)printf("There are no records\n");
                for (int i = 0; i <= id; i++) displayRecord(table, &i);
                break;
            case 3:
                table = fileImport(&id);
                break;
            case 4:
                fileExport(table, &id);
                break;
            case 5:
                printf("Which one?\n");
                scanf("%d", &choice);
                if (choice - 1 > id) {
                    printf("There is no such record\n");
                    break;
                }
                editRecord(table, choice - 1);
                break;
            case 6:
                printf("Which one?\n");
                scanf("%d", &choice);
                if (choice - 1 > id) {
                    printf("There is no such record\n");
                    break;
                }
                deleteRecord(table, choice - 1, &id);
                break;
            case 7:
                printf("By what?\n1.Phone number\n2.Call date\n3.Call duration\n4.City code\n");
                scanf("%d", &choice);
                if (choice < 1 || choice > 4) {
                    printf("Invalid value\n");
                    break;
                }
                sortList(choice, table, &id);
                break;
            case 8:
                printf("By what?\n1.Phone number\n2.Call date\n3.Call duration\n4.City code\n");
                scanf("%d", &choice);
                if (choice < 1 || choice > 4) {
                    printf("Invalid value\n");
                    break;
                }
                searchInList(choice, table, &id);
                break;
            case 9:
                printf("1.Total call duration of all\n2.Total call duration of certain number\n");
                scanf("%d", &choice);
                calculateInList(choice, table, &id);
                break;
            case 10:
                flag = 0;
                break;
            default:
                printf("Invalid value\n");
                break;
        }
    }
    return 0;

}

List* addRecord(List *tmpp, int *f_id) {

    (*f_id)++;
    List* tmp=malloc(sizeof(List));
    tmp=tmpp;
    tmp=(List*)realloc(tmp, ((*f_id)+1)*sizeof(List));
    printf("Enter phone number:8 **********\n");
    scanf("%lld", &tmp[*f_id].ph_num);
    while (1) {
        printf("Enter conversation date(dd,mm,yy):\n");
        scanf("%d %d %d", &tmp[*f_id].dd, &tmp[*f_id].mm, &tmp[*f_id].yy);
        if ((tmp[*f_id].dd <= 31) && (tmp[*f_id].mm <= 12) && (tmp[*f_id].yy > 0)) break;
        else (printf("Wrong date\n"));
    }
    while (1) {
        printf("Enter conversation duration(mm.ss):\n");
        scanf("%f", &tmp[*f_id].dur);
        if (tmp[*f_id].dur < 999.0) break;
        else printf("Too long, I don't believe\n");
    }
    while (1) {
        printf("Enter city code(if not, enter zero)\n");
        scanf("%d", &tmp[*f_id].city_code);
        if (tmp[*f_id].city_code < 999) break;
        else printf("Invalid number\n");
    }
    printf("Your record is: ");
    displayRecord(tmp, f_id);
    return tmp;
}

void editRecord(List *tmp, int q) {

    int p, flag = 1;
    while (flag) {
        printf("What value?\n1.Phone number\n2.Conversation date\n"
               "3.Conversation duration\n4.City code\n5.Entire record\n");
        scanf("%d", &p);
        switch (p) {
            case 1:
                printf("Enter phone number:8 **********\n");
                scanf("%lld", &tmp[q].ph_num);
                flag = 0;
                break;
            case 2:
                printf("Enter conversation date(dd,mm,yy):\n");
                scanf("%d %d %d", &tmp[q].dd, &tmp[q].mm, &tmp[q].yy);
                flag = 0;
                break;
            case 3:
                printf("Enter conversation duration(mm.ss):\n");
                scanf("%f", &tmp[q].dur);
                flag = 0;
                break;
            case 4:
                printf("Enter city Code(if not, enter zero)\n");
                scanf("%d", &tmp[q].city_code);
                flag = 0;
                break;
            case 5:
                printf("Enter phone number:8 **********\n");
                scanf("%lld", &tmp[q].ph_num);
                printf("Enter conversation date(dd,mm,yy):\n");
                scanf("%d %d %d", &tmp[q].dd, &tmp[q].mm, &tmp[q].yy);
                printf("Enter conversation duration(mm.ss):\n");
                scanf("%f", &tmp[q].dur);
                printf("Enter city Code(if not, enter zero)\n");
                scanf("%d", &tmp[q].city_code);
                flag = 0;
                break;
            default:
                printf("Invalid value\n");
        }
    }
    printf("Your record is:");
    displayRecord(tmp, &q);
}

void deleteRecord(List *tmp, int q, int *f_id) {

    if (*f_id <= -1) {
        printf("There are no records\n");
        return;
    }
    for (int i = q; i < *f_id; i++)
        tmp[i] = tmp[i + 1];
    (*f_id)--;
    tmp = realloc(tmp, sizeof(List) * (*f_id + 1));
    printf("Successfully deleted\n");
}

void sortList(int p, List *tmp, int *f_id) {

    if (*f_id == -1) {
        printf("There are no records\n");
        return;
    }
    List buff;
    switch (p) {
        case 1:
            for (int i = *f_id; i >= 0; i--) {
                int flag = 1;
                for (int j = 0; j < i; j++) {
                    if (tmp[j].ph_num > tmp[j + 1].ph_num){
                        buff = tmp[j];
                        tmp[j] = tmp[j + 1];
                        tmp[j + 1] = buff;
                        flag = 0;
                    }
                }
                if (flag == 1)
                    break;
            }
            break;
        case 2:
            for (int i = *f_id; i >= 0; i--) {
                int flag = 1;
                for (int j = 0; j < i; j++) {
                    if ((tmp[j].yy > tmp[j + 1].yy) || ((tmp[j].yy == tmp[j + 1].yy) && (tmp[j].mm > tmp[j + 1].mm)) ||
                        ((tmp[j].yy == tmp[j + 1].yy) && (tmp[j].mm == tmp[j + 1].mm) && (tmp[j].dd > tmp[j + 1].dd))) {
                        buff = tmp[j];
                        tmp[j] = tmp[j + 1];
                        tmp[j + 1] = buff;
                        flag = 0;
                    }
                }
                if (flag == 1)
                    break;
            }
            break;
        case 3:
            for (int i = *f_id; i >= 0; i--) {
                int flag = 1;
                for (int j = 0; j < i; j++) {
                    if (tmp[j].dur > tmp[j + 1].dur) {
                        buff = tmp[j];
                        tmp[j] = tmp[j + 1];
                        tmp[j + 1] = buff;
                        flag = 0;
                    }
                }
                if (flag == 1)
                    break;
            }
            break;
        case 4:
            for (int i = *f_id; i >= 0; i--) {
                int flag = 1;
                for (int j = 0; j < i; j++) {
                    if (tmp[j].city_code > tmp[j + 1].city_code) {
                        buff = tmp[j];
                        tmp[j] = tmp[j + 1];
                        tmp[j + 1] = buff;
                        flag = 0;
                    }
                }
                if (flag == 1)
                    break;
            }
            break;
    }
    printf("Successfully sorted\n");

}

void searchInList(int p, List *tmp, int *f_id) {

    if (*f_id == -1) {
        printf("There are no records\n");
        return;
    }
    List arr[10];
    long long int y;
    int x1, x2, x3, delta = 100000000, j = -1, k = -1;
    float f1;
    double ddelta = 1000;
    switch (p) {
        case 1:
            printf("Enter value:\n");
            scanf("%lld", &y);
            for (int i = 0; i <= j; i++)
                if (abs(arr[i].ph_num - y) < delta)
                    delta = abs(arr[i].ph_num - y);
            for (int i = 0; i <= j; i++)
                if ((abs(arr[i].ph_num - delta) == y) || (abs(-delta - arr[i].ph_num) == y))
                    displayRecord(arr, &i);
            break;
        case 2:
            printf("Enter date:\n");
            scanf("%d %d %d", &x1, &x2, &x3);
            for (int i = 0; i <= *f_id; i++)
                if (abs(tmp[i].yy - x3) < delta)
                    delta = abs(tmp[i].yy - x3);
            for (int i = 0; i <= *f_id; i++) {
                if ((abs(tmp[i].yy - delta) == x3) || (abs(-delta - tmp[i].yy) == x3)) {
                    j++;
                    arr[j] = tmp[i];
                }
            }
            delta = 1000000000;
            for (int i = 0; i <= j; i++)
                if (abs(arr[i].mm - x2) < delta)
                    delta = abs(arr[i].mm - x2);
            for (int i = 0; i <= j; i++)
                if ((abs(arr[i].mm - delta) == x2) || (abs(-delta - arr[i].mm) == x2)) {
                    k++;
                    arr[k] = arr[i];
                }
            delta = 1000000000;
            for (int i = 0; i <= k; i++)
                if (abs(arr[i].dd - x1) < delta)
                    delta = abs(arr[i].dd - x1);
            for (int i = 0; i <= k; i++)
                if ((abs(arr[i].dd - delta) == x1) || (abs(-delta - arr[i].dd) == x1)) displayRecord(arr, &i);
            break;
        case 3:
            printf("Enter value:\n");
            scanf("%f", &f1);
            for (int i = 0; i < *f_id; i++)
                if (fabs(tmp[i].dur - f1) < ddelta)
                    ddelta = fabs(tmp[i].dur - f1);
            for (int i = 0; i < *f_id; i++)
                if ((tmp[i].dur == f1) || (fabs(tmp[i].dur - ddelta) == f1) || (fabs(-ddelta - tmp[i].dur) == f1))
                    displayRecord(tmp, &i);
            break;
        case 4:
            printf("Enter value:\n");
            scanf("%d", &x1);
            for (int i = 0; i < *f_id; i++)
                if (abs(tmp[i].city_code - x1) < delta)
                    delta = abs(tmp[i].city_code - x1);
            for (int i = 0; i < *f_id; i++)
                if ((tmp[i].city_code == x1) || (abs(tmp[i].city_code - delta) == x1) ||
                    (abs(-delta - tmp[i].city_code) == x1))
                    displayRecord(tmp, &i);
            break;
    }

}

void calculateInList(int p, List *tmp, int *f_id) {

    if (*f_id == -1) {
        printf("There are no records\n");
        return;
    }
    double total_dur = 0;
    int x1, x2;
    switch (p) {
        case 1:
            for (int i = 0; i < *f_id; i++)
                total_dur += tmp[i].dur;

            printf("%5.2f\n", total_dur);
            break;
        case 2:
            printf("What phone number?\n");
            scanf("%lld", &x1);
            for (int i = 0; i < *f_id; i++)
                if (tmp[i].ph_num == x1)
                    total_dur += tmp[i].dur;
            if (total_dur == 0)
                printf("There are no such phone numbers\n");
            else
                printf("%5.2f\n", total_dur);
            break;
    }
}

void displayRecord(List *out, int *o_id) {

    printf("id-%02d | ", (*o_id) + 1);
    printf("8 %10lld | %02d.%02d.%04d | %05.2f | %03d\n", out[*o_id].ph_num, out[*o_id].dd,
           out[*o_id].mm, out[*o_id].yy, out[*o_id].dur, out[*o_id].city_code);
}

List* fileImport(int *f_id) {

    List* tmp = (List*)malloc(sizeof(List));
    char c;
    int str_num = 0;
    FILE *file;
    file = fopen("SavedRecords.txt", "r");
    for (int i = 0; i < 32767; i++) {
        fscanf(file, "%c", &c);
        if (c == '\n') str_num++;
    }
    fclose(file);
    file = fopen("SavedRecords.txt", "r");
    for (int i = 0; i <= str_num; i++) {
        (*f_id)++;
        tmp=(List*)realloc(tmp, sizeof(List)*(*f_id+1));
        fscanf(file, "%lld", &tmp[*f_id].ph_num);
        fscanf(file, " %d %d %d", &tmp[*f_id].dd, &tmp[*f_id].mm, &tmp[*f_id].yy);
        fscanf(file, " %f", &tmp[*f_id].dur);
        fscanf(file, " %d\n", &tmp[*f_id].city_code);
    }
    fclose(file);
    printf("Successfully imported\n");
    return tmp;
}

void fileExport(List *tmp, int *f_id) {

    FILE *file;
    file = fopen("SavedRecords.txt", "w+");
    for (int j = 0; j < *f_id; j++)
        fprintf(file, "%010d %02d %02d %04d %05.2f %03d\n", tmp[j].ph_num, tmp[j].dd, tmp[j].mm,
                tmp[j].yy, tmp[j].dur, tmp[j].city_code);
    fprintf(file, "%010d %02d %02d %04d %05.2f %03d", tmp[*f_id].ph_num, tmp[*f_id].dd,
            tmp[*f_id].mm, tmp[*f_id].yy, tmp[*f_id].dur, tmp[*f_id].city_code);
    fclose(file);
}
