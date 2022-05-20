#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define tenKB 10*1024

int main(int argc, char *argv[], char *envp[]) {

    int fd;
    if((fd = open("3lab1.c", O_RDONLY)) < 0){

        /* Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу */

        printf("Can\'t open file\n");
        exit(-1);
        } 
    char* str;
    str = (char*)malloc(tenKB*sizeof(char));
    int size = read(fd,str,tenKB);
    str[tenKB] = 0;
    close(fd);
    char* file = "1lab.c";
        int shmID; 
        key_t key;
        key = ftok(file, 0);
        if(key < 0){
        printf("Cant make a key\n");
        exit(-1);
        }
        shmID = shmget(key, tenKB*sizeof(char), 0666|IPC_CREAT|IPC_EXCL);
        if (shmID < 0 ) {
            if (errno != EEXIST) {
                printf("Error allocating shared memory\n");
                exit(-1);
            }
            else {
                if ((shmID = shmget(key, tenKB*sizeof(char), 0)) < 0) {
                    printf("Cant find shared memory\n");
                    exit(-1);
                }
            }
        }
        char* shared;
        shared = (char*)shmat(shmID, NULL, 0); 
        if (shared == (char*)(-1)) {
            printf("Cant attach memory\n");
            exit(-1);
        }
        memcpy(shared, str, tenKB);
        printf("Copied\n");
    return 0;
}