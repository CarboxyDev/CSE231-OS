#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/shm.h>
#include <time.h>

#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1000
#define LINUX_CODE 06666
#define SHM_KEY 9999

/**
 * This is P1 using Shared Memory (shm) IPC mechanism.
*/

void buildRandomStr(char *p) {
    // this function does not require returning any value as it modifies the memory of the strings itself
    char *build = p;
    for (int i = 0; i < STR_LEN; i++) {
        int r_char_ascii = rand() % 26;
        *build = r_char_ascii + ASCII_START;
        build++;
    }

};

void startShm() {
    char *arrayOfStrings[STR_COUNT];
    for (int i = 0; i < STR_COUNT; i++) {
        arrayOfStrings[i] = malloc(8 * sizeof(char)); // allocate 8 bytes for every string
        buildRandomStr(*(arrayOfStrings + i));
    }

    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];

    memset(readBuffer, 0, BUFFER_SIZE);
    memset(writeBuffer, 0, BUFFER_SIZE);

    int shmid = shmget(SHM_KEY, BUFFER_SIZE, 0666 | IPC_CREAT);

    if (shmid < 0) {
        printf("[ERROR] Could not create Shared Memory segment\n");
        return;
    }
    
    void* sharedMem = shmat(shmid, NULL, 0);
    if (sharedMem == (void*)-1) {
        printf("[ERROR] Could not attach to shared memory\n");
        return;
    }

    printf("[READY] P1 using shm\n");
    
    int f;
    int writeMsg;
    int writeIndex;
    writeIndex = 0;


}


int main() {
    startShm();
    return 0;
}