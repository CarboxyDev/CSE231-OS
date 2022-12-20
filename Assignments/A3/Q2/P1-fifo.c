#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <time.h>

#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1000
#define LINUX_CODE 06666


/**
 * This is P1 using FIFO IPC mechanism.
 */

void buildRandomStr(char *p) {
    // this function does not require returning any value as it modifies the memory of the strings itself
    char *build = p;
    for (int i = 0; i < STR_LEN; i++) {
        int r_char_ascii = rand() % 26;
        *build = r_char_ascii + ASCII_START;
        build++;
    }

}

void startFIFO() {
    char *arrayOfStrings[STR_COUNT];
    for (int i = 0; i < STR_COUNT; i++) {
        arrayOfStrings[i] = malloc(8 * sizeof(char)); // allocate 8 bytes for every string
        buildRandomStr(*(arrayOfStrings + i));
    }


    mkfifo("/tmp/fifo", LINUX_CODE); // creates the fifo
    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];

    memset(readBuffer, 0, BUFFER_SIZE);
    memset(writeBuffer, 0, BUFFER_SIZE);

    printf("[READY] P1 using FIFO pipes\n");
    int f;
    int writeMsg;
    int writeIndex;
    writeIndex = 0;

    while (1 == 1) {
        f = open("/tmp/fifo", O_WRONLY);
        if (f < 0) {
            printf("[ERROR] Cannot write to FIFO.\n");
        }
        else { // writing the message in FIFO
            snprintf(writeBuffer, 128, "%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n", writeIndex, *(arrayOfStrings + writeIndex),
                writeIndex + 2, *(arrayOfStrings + writeIndex + 2), writeIndex + 1, *(arrayOfStrings + writeIndex + 1),
                writeIndex + 3, *(arrayOfStrings + writeIndex + 3), writeIndex + 4, *(arrayOfStrings + writeIndex + 4));
            
            
            printf("[INFO] Data sent by P1:\n%s", writeBuffer);
            writeMsg = write(f, writeBuffer, BUFFER_SIZE);
            printf("[STATUS] Message has been written\n");

            close(f);
            f = open("/tmp/fifo", O_RDONLY);
            if (f  < 0) {
                printf("[ERROR] Cannot read FIFO");
            }

            read(f, readBuffer, BUFFER_SIZE);
            close(f);

            printf("Received Data from P2: %s\n", readBuffer);
            int recvData = atoi(readBuffer);
            if ((writeIndex + 4) == recvData) {
                writeIndex += 5;
            }
            else if ((writeIndex + 4) != recvData) {
                printf("[Failure in data stream]");
            };

            if (writeIndex >= 50) { // i.e the limit is reached
                break;
            }
        }
    };

    printf("[END] P1\n");
    unlink("/tmp/fifo"); // destroy the FIFO
}



int main() {

    clock_t start = clock();
    startFIFO();
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by FIFO: %f seconds\n", timeTaken);

    return 0;
}