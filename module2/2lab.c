#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include <locale.h>

int arrDim(char* s) {
    int j;
    char tmp[100];
    for (int i = 1; s[i] != '\0'; i++) {
        if(s[i] == 'd' || s[i] == 'f') {
            for(j = 0; j < i; j++) {
                tmp[j] = s[j+1];
            }
            tmp[j+1] = '\0';
        }
    }
    return atoi(tmp);
}
char* read(char* s) {
   for(int i =0; s[i]!='\0'; i++) {
       int j = 0;
       if (s[i] == 'f' || s[i] == 'd' || s[i] ==',' || isdigit(s[i]) || s[i] == ' ') {
           if((isdigit(s[i]) && s[i+1] == 'd' ) ||( isdigit(s[i]) && s[i+1] == 'f' )) {
               continue;
           }
           else {
               if(s[i+1] == ',' || (s[i] == ',' && isdigit(s[i+1])))
                printf("%c", s[i]);
                else {
                    printf("%c ", s[i]);
                }
           }
       }
}
}
char* func(char **f_string, int num)
{
	int i, j;
	char* result;
    result = (char*)malloc(sizeof(char)*100);
	char d[16];
	char f[16];
    int resI = 0;

for(int k = 0; k < num; k++) {
for (i = 0; f_string[k][i] != '\0'; i++)
{       
		if (f_string[k][i] == 'd')
		{
			if ((isdigit(f_string[k][i - 1])) == 0)
			{
                strcat(result, f_string[k]);
				printf("Введите целое число: \n");
				scanf("%s", d);
				strcat(result, d);
                //strcat(result, " ");
			}
		}

		if (f_string[k][i] == 'f')
		{
			if ((isdigit(f_string[k][i - 1])) == 0)
			{
                strcat(result, f_string[k]);
				printf("Введите вещественное число: \n");
				scanf("%s", f);
				strcat(result, f);
               // strcat(result, " ");
			}
		}

		if ((f_string[k][i] == 'd') && ((isdigit(f_string[k][i - 1]))))
		{
            strcat(result, f_string[k]);
			printf("Введите числа для массива целых чисел\n");
			for (j = 0; j < arrDim(f_string[k]); j++)
			{
				scanf("%s", d);
				strcat(result, d);
               // strcat(result, " ");
			}

		}

		if ((f_string[k][i] == 'f') && ((isdigit(f_string[k][i - 1]))))
		{
            strcat(result, f_string[k]);
			printf("Введите числа для массива вещественных чисел\n");
			for (j = 0; j < arrDim(f_string[k]); j++)
			{
				scanf("%s", f);
				strcat(result, f);
                //strcat(result, " ");
			}

		}

	}
}
	return result;
}
int main()
{
    int num;
	setlocale(LC_ALL, "Rus");
	char f_string[50];
    printf("Сколько чисел заданного формата будет упаковано?\n");
    scanf("%d", &num);
    char** str;
    str = (char**)malloc(num*sizeof(char*));
    for(int i = 0; i < num; i++) {
        str[i] = (char*)malloc(50*sizeof(char));
    }
    for(int i = 0; i < num; i++) {
        printf("Введите форматную строку\n");
	    scanf("%s", f_string);
        int j = 0;
        for(; f_string[j]!='\0'; j++) {
            str[i][j] = f_string[j];
        }
        str[i][j] = '\0';
    } 
    char* res = func(str, num);
    read(res);
	return 0;

}