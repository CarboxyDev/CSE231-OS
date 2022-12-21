#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>


#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1024
#define LINUX_CODE 06666
#define CHAR_COUNT 8
#define ITER_COUNT 10
#define KEY 0x1234

int main () {
    int iterator = ITER_COUNT;
    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];

    memset(readBuffer, 0, BUFFER_SIZE);
    memset(writeBuffer, 0, BUFFER_SIZE);

    int shmid = shmget(KEY, BUFFER_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("[ERROR] Unable to create shared memory\n");
        return 1;
    }

    // Attach shared memory segment to this process
    void *sharedMem = shmat(shmid, NULL, 0);
    if (sharedMem == (void*) - 1) {
        perror("[ERROR] Unable to attach shared memory\n");
        return 1;
    };

    int writeMsg;
    int IndexLimitMax = -1;
    int IndexLimitMax_prev = -1;

    int c = 0;
    while (iterator) {
        sscanf((char*) sharedMem, "%d%*s", &IndexLimitMax);
        printf("[INFO] Data received from P1:\n%s", sharedMem);
        
        if (IndexLimitMax_prev != IndexLimitMax) {
            IndexLimitMax_prev = IndexLimitMax;
            iterator -= 1;
        };

        int newIndexLimitMax = IndexLimitMax + 4;
        snprintf(sharedMem, CHAR_COUNT, "%d", newIndexLimitMax);
        printf("[STATUS] Message has been sent\n");
        printf("Message sent: %s\n", sharedMem);
        sleep(2);
    };

    printf("[END] P2\n");
    shmdt(sharedMem);

}