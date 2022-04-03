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
int main() {
    char* text;
    char* file = "1lab.c";
    int fd;
    if(fd = open(file, O_RDONLY) < 0) {
        printf("No keyfile exits");
        exit(-1);
    }
    close(fd);
    int shmID; 
    key_t key;
    key = ftok(file, 0);
    if(key < 0){
    printf("Cant make a key\n");
    exit(-1);
    }
    if ((shmID = shmget(key, tenKB*sizeof(char), 0)) < 0) {
                    printf("Cant find shared memory\n");
                    exit(-1);
                }
    printf("Shmid: %d\n", shmID);
    text = (char*)shmat(shmID, NULL, SHM_RDONLY);
    if (text == (void*)(-1)) {
        printf("Cant attach memory\n");
        exit(-1);       
    }
    printf("Text:\n%s", text);
     if (shmctl(shmID, IPC_RMID, NULL) < 0) {
        printf("Cant remove shared memory\n");
        exit(-1); 
    }

    return 0;

}