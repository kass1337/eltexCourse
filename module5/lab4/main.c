/*Статистический анализ. Имеется несколько массивов данных (разного размера). 
Требуется определить математическое ожидание в каждом массиве. 
Обработка каждого массива выполняется в отдельном процессе.*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS               0
#define NUM 3
int randomInt(int min, int max) {

    return min + rand()%max;
}
typedef struct arguments_tag {
    int id;
    int* mat;
    int dim;
} arguments;
void* thread_calcVariance(void* args) {
    arguments *arg = (arguments*) args;
    int* Arr = arg->mat;
    int N = arg->dim;
    int pid = arg->id;
    double tmp = 0.0;
    for (int i = 0; i < N; i++) {
        tmp += Arr[i];
    }

    printf("ID: %d\n", pid);
    printf("Value: %f\n", (double)(tmp / (double)N));
} 
int main(){
    srand(time(0));
    int dims[NUM] = {randomInt(10,20), randomInt(30, 40), randomInt(50, 60)};
    int** mat;
    int status_addr;
    int status = 0;
    mat = (int**)malloc(sizeof(int*) * NUM);
    pthread_t threads[NUM];
    arguments args[NUM];
    for(int i = 0; i < NUM; i++) {
        args[i].id = i+1;
        for(int j = 0; j < dims[i]; j++) {
            mat[i] = (int*)malloc(sizeof(int)*dims[i]);
            mat[i][j] = randomInt(100,1000);
        }
        args[i].mat = mat[i];
        args[i].dim = dims[i];
        pthread_create(&threads[i], NULL, thread_calcVariance, (void*) &args[i]);
    }
    for (int i = 0; i < NUM; i++) {
    status = pthread_join(threads[i], (void**)&status_addr);
    if (status != SUCCESS) {
        printf("main error: can't join thread, status = %d\n", status);
        exit(ERROR_JOIN_THREAD);
    }
}
    return 0;
}
