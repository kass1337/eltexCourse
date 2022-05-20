#include "stdio.h"
#include "stdlib.h"
#include <string.h> 

int FindNumber(char* str) //FindNumber ищет первое число в строке
{
	int num = 0;
	for (int i = 0; str[i] >= '0' && str[i] <= '9'; ++i)
	{
		num = (str[i] - '0');
	}
	return num;
}

int FindWordIndex(char* str, int WordIndex) // функция ищет индекс начала слова, который нумеруется WordIndex
{
	int n = 0;
	if (str[0] != ' ')
	{
		if (WordIndex == ++n) return 0;
	}

	
	for (int i = 1; str[i] != '\0'; ++i)
	{
		if (str[i - 1] == ' ' && str[i] != ' ')
		{
			if (WordIndex == ++n) return i;
		}
	}
	return -1;
}

int FindWordCount(char* str) //ищет количество слов
{
	int n = 0;
	if (str[0] != ' ')
	{
		n++;
	}
	for (int i = 1; i < str[i] != '\0'; ++i)
	{
		if (str[i - 1] == ' ' && str[i] != ' ') ++n;
	}
	return n;
}

void WordPut(char* str, char* word) //Вставляет первое слово из строки word в начало строки str
{
	// буфер
	char temp[100] = { '\0' };

	int i = 0;

	for (i = 0; word[i] != ' ' && word[i] != '\0'; ++i)
	{
		temp[i] = word[i];
	}

	int j = 0;

	for (; str[j] >= '0' && str[j] <= '9'; ++j);

	for (; str[j] != '\0' && i < 100 && j < 100; ++i, ++j)
	{
		temp[i] = str[j];
	}

	
	for (j = 0; temp[j] != '\0'; ++j)
	{
		str[j] = temp[j];	
	}
	str[strlen(str)] = '\0';

}

char* foo(char* str)
{
	// главная функция, реализующая алгоритм

	// буфер
	char* temp = (char*)malloc(100*(sizeof(char)));
	for (int i = 0; i < 100; ++i)
	{
		temp[i] = str[i];
		if (temp[i] == '\0') break;
	}

	// Нахождение кол-ва слов в строке
	int WordCount = FindWordCount(str);

	//Главный цикл строки
	for (int i = 0; temp[i] != '\0'; ++i)
	{
		// Поиск символа-цифры
		if (temp[i] >= '0' && temp[i] <= '9')
		{
			//Номер слова
			int WordIndex = FindNumber(temp + i);

			//Пропуск, если номер слова больше кол-ва слов
			if (WordIndex > WordCount)
			{
				continue;
			}
			// начало слова под номером WordIndex
			int WordStart = FindWordIndex(str, WordIndex);


			// перенос позиции в строке
			// на длину вставленного слова
			WordPut(temp + i, str + WordStart);
		}
	}
	// здесь буфер - результат
	return temp;
}

int main()
{
	char str[1000] = { 0 };
	fgets(str, 1000, stdin);
	// длина входной строки
	char* res = foo(str);
	for (int i = 0; res[i]!='\n'; i++)
	{
		printf("%c", res[i]);
	}
    printf("\n");
	return 0;
}
