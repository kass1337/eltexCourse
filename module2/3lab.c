#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATE_L 100
#define SUR_L 100
struct call
{
	char surname[100];
	int amount;
    int* dur;
    char** date;
};
void addCall(struct call* c, int* len)
{

	char s[100];
	char* d;
    d = (char*)malloc(DATE_L*sizeof(char));
	int _amount;
	int tmp = 0;
    int _dur;
	printf("Введите фамилию:\n");
	scanf("%s", s);

	printf("Введите количество:\n");
	scanf("%d", &_amount);
    c[*len].dur=(int*)malloc(_amount*sizeof(int));
    c[*len].date=(char**)malloc(_amount*sizeof(char*));
    for(int i = 0; i <_amount; i++) c[*len].date[i] = (char*)malloc(DATE_L * sizeof(char));
    strcpy(c[*len].surname, s);
    c[*len].amount = _amount;
    while (tmp < _amount) {
	printf("Введите продолжительность:\n");
	scanf("%d",&_dur);
    printf("Введите дату:\n");
	scanf("%s", d);
    c[*len].dur[tmp] = _dur;
    strcpy(c[*len].date[tmp], d);
    tmp++;
    }
	(*len)++;
}

void removeCall(struct call* c, int* len)
{
	int id;
	printf("Введите номер:\n");
	scanf("%d", &id);

	if (id < 0 || id >= *len) {
		printf("Ошибка\n");
		return;
	}
	for (int i = id; i < *len; i++) {
		strcpy(c[i].surname, c[i + 1].surname);
		c[i].amount = c[i + 1].amount;

        free(c[i].dur);
        c[i].dur = (int*)malloc(sizeof(int)*c[i].amount);
        for(int j = 0; j < c[i].amount; j++) free(c[i].date[j]);
        free(c[i].date);
        c[i].date = (char**)malloc(sizeof(char*)*c[i+1].amount);
        for(int j = 0; j < c[i+1].amount; j++) c[i].date[j] = (char*)malloc(DATE_L*sizeof(char));

        for(int j = 0; j < c[i+1].amount; j++) {
            c[i].dur[j] = c[i+1].dur[j];
            strcpy(c[i].date[j], c[i+1].date[j]);
        }
	}
	(*len)--;
}
void editCall(struct call* c, int* len)
{
	int id;
	char s[100];
	int _amount;
    int _dur;
    char* d;
    d = (char*)malloc(DATE_L*sizeof(char));
    int tmp = 0;
	printf("Введите номер:\n");
	scanf("%d", &id);

	if (id < 0 || id >= *len) {
		printf("Неверно указан ID записи\n");
		return;
	}
	printf("Введите фамилию:\n");
	scanf("%s", s);
	printf("Введите количество:\n");
	scanf("%d", &_amount);
    strcpy(c[id].surname, s);
    c[id].amount = _amount;
    free(c[id].dur);
    for(int i = 0; i<c[id].amount; i++) free(c[id].date[i]);
    free(c[id].date);
    c[id].dur=(int*)malloc(sizeof(int)*_amount);
    c[id].date=(char**)malloc(sizeof(char*)*_amount);
    for(int i = 0; i < _amount; i++) c[id].date[i] = (char*)malloc(DATE_L * sizeof(char));
    while(tmp < _amount) {
        printf("Введите дату:\n");
        scanf("%s", d);
        printf("Введите продолжительность:\n");
        scanf("%d", &_dur);
        stpcpy(c[id].date[tmp], d);
        c[id].dur[tmp] = _dur;
        tmp++;
    }
	printf("Изменено\n");
}

void showTable(struct call* c, int* len)
{
    if(*len == 0) {
        printf("Нечего показывать\n");
        return;
    }
	for (int i = 0; i < *len; i++) {
		printf(	"ID: %d\t"
			"Фамилия: %s\t"
			"Количество: %d\t", i, c[i].surname,
			c[i].amount);
            for(int j = 0; j < c[i].amount; j++) {
                printf("\nДата: %s\n", c[i].date[j]);
                printf("\nПродолжительность: %d\n", c[i].dur[j]);
            }
	}
}
void searchName(struct call* c, int* len) {
    int i, j, maxs = 0, s = 0, minr = 1000, r = 0;
		int otv = 0;
		char* sur;
        sur = (char*)malloc(SUR_L*sizeof(char));
		printf("Введите фамилию: ");
		scanf("%s", sur);
		for (i = 0; i < *len; i++) {
			for (j = 0; sur[j] != '\0' && r == 0; j++) {
				if (c[i].surname[j] == sur[j]) {
					s++;
				}
				else {
					r = r + abs(c[i].surname[j] - sur[j]);
				}
			}
			if (s > maxs) {
				otv = i;
				maxs = s;
				minr = r;
			}
			if (s == maxs) {
				if (r < minr) {
					otv = i;
					minr = r;
				}
			}
			s = 0;
			r = 0;
		}
        printf("Результат поиска: \n");
		printf("Фамилия:%s\tКоличество:%d\t", c[otv].surname, c[otv].amount);
        for(int k = 0; k < c[otv].amount; k++) printf("Дата: %s\tПродолжительность:%d\t",
          c[otv].date[k], 
          c[otv].dur[k]);
}
void searchAmount(struct call* c, int* len) {
    int find;
    printf("Введите количество: ");
	scanf("%d", &find);
    int i = 0;
    int found = 0;
    int j;
    for(; i < (*len); i++) {
        if(find == c[i].amount) {
            found = 1;
            j = i;
        }
    }
    if(found == 1) {
        printf("Результат поиска: \n");
		printf("Фамилия:%s\tКоличество:%d\t", c[j].surname, c[j].amount);
        for(int k = 0; k < c[j].amount; k++) printf("Дата: %s\tПродолжительность:%d\t",
          c[j].date[k], 
          c[j].dur[k]);
          return;
    }
    else {
       for(i = 0; i < (*len); i++) {
        if(find+1 == c[i].amount || find -1 == c[i].amount) {
            found = 1;
            j = i;
        }
    } 
    }
    if(found == 1) {
        printf("Результат поиска: \n");
		printf("Фамилия:%s\tКоличество:%d\t", c[j].surname, c[j].amount);
        for(int k = 0; k < c[j].amount; k++) printf("Дата: %s\tПродолжительность:%d\t",
          c[j].date[k], 
          c[j].dur[k]);
    }
    else {
        printf("Не найдено\n");
    }
         
}
void sumAmount(struct call* c, int* len) {
    int sum = 0;
    for(int i =0; i<*len;i++)
    {
        sum+=c[i].amount;
    }
    printf("Сумма количества переговоров: %d\n", sum);
}
void sort(struct call* c, int* len) {
    int sw;
    printf("По какому полю сортировать?\n1.Фамилии\n2.Количеству переговоров\n");
    scanf("%d", &sw);
    switch(sw){
        case 1: {
        struct call temp;
        for(int i = 0; i < (*len); i++) {
            for(int j = 0; j < (*len) - j - 1; j++) {
                if(strcmp(c[j].surname, c[j+1].surname )) {
                    temp = c[j];
                    c[j] = c[j+1];
                    c[j+1] = temp;
                }
            }
        }
        break;
        }
        case 2: {
            struct call temp;
        for(int i = 0; i < (*len); i++) {
            for(int j = 0; j < (*len) - j; j++) {
                if(c[j].amount > c[j+1].amount) {
                    temp = c[j];
                    c[j] = c[j+1];
                    c[j+1] = temp;
                }
            }
        }
        break;
        }
    }
}

void saveTable(struct call* c, int* len)
{
    FILE* f;
	f = fopen("log.txt", "w");
	if (f == NULL) {
		printf("Ошибка\n");
		return;
	}

	fprintf(f, "%d\n", (*len));

	for(int i = 0; i < (*len); i++) {
		fprintf(f, "%s\n%d\n", c[i].surname,
			c[i].amount);
        for(int j = 0; j < c[i].amount; j++) {
            fprintf(f,"%s\n%d\n", c[i].date[j], c[i].dur[j]);
        }
	}
    fclose(f);
}

void loadTable(struct call* c, int* len)
{
	FILE* f;
    char a[1];
	f = fopen("log.txt", "r");
	if (f == NULL) {
		printf("Ошибка\n");
		return;
	}
    char* tmpLen;
    tmpLen = (char*)malloc(sizeof(char)*100);
    fgets(tmpLen, sizeof(int), f);
    (*len) = atoi(tmpLen);
	for(int i = 0; i < (*len); i++) {
		fgets(c[i].surname, 1000, f);
        fscanf(f, "%d\n", &c[i].amount);
        c[i].date = (char**)malloc(sizeof(char*)*c[i].amount);
        c[i].dur = (int*)malloc(sizeof(int)*c[i].amount);
        for(int j = 0; j < c[i].amount; j++) {
            c[i].date[j] = (char*)malloc(sizeof(char)*DATE_L);
            fgets(c[i].date[j], 1000, f);
            fscanf(f, "%d\n" , &c[i].dur[j]);
        }
	}
    fclose(f);
}
int main()
{
    int tableLen = 0;
    struct call calls[100];
    struct call tmp[100];
	int menu;
	while(1) {
		printf(	"Выберите пункт меню:\n"
			"1. Добавить запись\n"
			"2. Удалить запись\n"
			"3. Редактировать запись\n"
			"4. Показать все записи\n"
			"5. Сортировка по заданному полю (по возрастанию)\n"
			"6. Сохранить базу данных\n"
			"7. Загрузить базу данных\n"
			"8. Сумма всех переговоров\n"
            "9. Поиск по фамилии\n"
            "10. Поиск по количеству переговоров\n"
			"> ");
		scanf("%d", &menu);
        if (menu < 0 || menu > 10) {
			printf("Выбран неверный пункт меню\n");
			continue;
		}
        switch(menu) {
            case 1:
            addCall(calls, &tableLen);
            break;
            case 2:
            removeCall(calls, &tableLen);
            break;
            case 3:
            editCall(calls, &tableLen);
            break;
            case 4:
            showTable(calls, &tableLen);
            break;
            case 5:
            sort(calls, &tableLen);
            break;
            case 6:
            saveTable(calls, &tableLen);
            break;
            case 7:
            loadTable(calls, &tableLen);
            break;
            case 8:
            sumAmount(calls, &tableLen);
            break;
            case 9:
            searchName(calls, &tableLen);
            break;
            case 10:
            searchAmount(calls, &tableLen);
            break;
        }
	}

	return 0;
}