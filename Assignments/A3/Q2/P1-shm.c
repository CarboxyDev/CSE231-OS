#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <time.h>

#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1024
#define LINUX_CODE 06666
#define SHM_KEY 0x1234

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

    int shmid = shmget(SHM_KEY, BUFFER_SIZE, IPC_CREAT | 0666 );

    if (shmid < 0) {
        printf("[ERROR] Could not create Shared Memory segment\n");
        return;
    }

    printf("Key: %d\n", shmid);

    void* sharedMem = shmat(shmid, NULL, 0);
    if (sharedMem == (void*) - 1) {
        printf("[ERROR] Could not attach to shared memory\n");
        return;
    }

    printf("Process attached at address: %p\n", sharedMem);

    printf("[READY] P1 using shm\n");    
    int f;
    int writeMsg;
    int writeIndex;
    writeIndex = 0;

    int idx = 0;
    while (idx < 50) {
        snprintf((char*) sharedMem, BUFFER_SIZE, "%d -> %s \n%d -> %s \n%d -> %s \n%d -> %s \n%d -> %s\n", idx, arrayOfStrings[idx], idx+1, arrayOfStrings[idx+1], idx+2, arrayOfStrings[idx+2], idx+3, arrayOfStrings[idx+3], idx+4, arrayOfStrings[idx+4]);

        printf("[INFO] Data sent by P1:\n%s", sharedMem);

        int ackw = 0;
        while (ackw < (idx + 1)) {
            sscanf((char*) sharedMem, "%d", &ackw);
            sleep(1);
        };
        
        printf("Received Data from P2: %s\n", sharedMem);

        idx += 5;

    }

    shmdt(sharedMem);



}


int main() {
    clock_t start = clock();
    startShm();
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by SHM: %f seconds\n", timeTaken);

    return 0;
}