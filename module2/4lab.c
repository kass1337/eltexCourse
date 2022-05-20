#include "stdlib.h"
#include "stdio.h"
#include "string.h"
int calcWords(char* str) {
    int words = 0;
    for(int i =0; str[i]!='\0'; i++) {
        if(str[i] == ' ') words++;
    }
    return words+1;
}

char** put(char* str) {
    int len = 0;
    char** arr;
    char** res;
    const int words = calcWords(str);
    int wordLen[words];
    int j = 0;
    for(int i = 0; i < words; i++){
        while(str[j]!= ' ' && str[j+1]!='\0') {
            len++;
            j++;
        }
        wordLen[i] = len;
        len = 0;
        j++;
    }
    int l = 0;
    arr = (char**)malloc(sizeof(char*)*words);
    for(int i = 0; i<words; i++) {
        arr[i] = (char*)malloc(sizeof(char)*wordLen[i]);
        int k = 0;
        while (k < wordLen[i]) {
            arr[i][k] = str[l];
            k++;
            l++;
            if(str[l] == ' ' || str[l] == '\0') {
                l++;
                break;
            }
        }
    }
    res = (char**)malloc(sizeof(char*)*words);
    for(int i = 0; i<words; i++) {
        res[i] = (char*)malloc(sizeof(char));
        res[i] = arr[i];
    }
    return res;
}
int main() {
    char* str;
    str = (char*)malloc(sizeof(char)* 100);
    char** fin;
    printf("Введите строку для помещения в динамический массив:\n");
    fgets(str, 100, stdin);
    fin = put(str);
    for(int i =0; i<calcWords(str); i++) {
        printf("%c ", *(fin)[i]);
    }
    printf("\n");
    return 0;
}