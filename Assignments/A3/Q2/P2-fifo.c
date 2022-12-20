#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>

#define CHAR_COUNT 8
#define BUFFER_SIZE 1000
#define ITER_COUNT 10

/**
 * This is P2 using FIFO IPC mechanism.
 */

int main() {
    int iterator = ITER_COUNT;
    char readBuffer[1000];
    char writeBuffer[1000];

    memset(readBuffer, 0, 1000);
    memset(writeBuffer, 0, 1000);

    printf("[READY] P2\n");
    int f;
    int writeMsg;
    int IndexLimitMax = -1;
    int IndexLimitMax_prev = -1;
    while (iterator) {
        f = open("/tmp/fifo", O_RDONLY);
        
        read(f, readBuffer, BUFFER_SIZE);
        printf("[INFO] Data received from P1:\n%s", readBuffer);

        sscanf(readBuffer, "%d%*s", &IndexLimitMax);
        if (IndexLimitMax_prev != IndexLimitMax) {
            IndexLimitMax_prev = IndexLimitMax;
            iterator -= 1;
        }

        close(f);
        int newIndexLimitMax = IndexLimitMax + 4;

        f = open("/tmp/fifo", O_WRONLY);
        snprintf(writeBuffer, CHAR_COUNT, "%d", newIndexLimitMax);
        printf("[STATUS] Message has been sent\n");
        printf("Message sent: %s\n", writeBuffer);
        writeMsg = write(f, writeBuffer, BUFFER_SIZE);
        close(f);
    }

    printf("[END] P2\n");
    close(f);
}