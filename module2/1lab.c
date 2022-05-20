#include "stdio.h"
#include "stdlib.h"


int countNumbers(char * str) {
    int k = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] <= '9' && str[i] > '0') {
            k++;
        } 
    }
    return k;
}




int main()
{
	char str[1000] = { 0 };
	fgets(str, 1000, stdin);
	// длина входной строки
	//char* res = foo(str);
    int k = countNumbers(str);
	for (int i = 0; str[i]!='\n'; i++)
	{
		printf("%d", k);
	}
	return 0;
}//5