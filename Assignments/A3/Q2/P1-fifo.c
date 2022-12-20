#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define STR_LEN 8
#define LINUX_CODE 06666

/**
 * This is P1 using FIFO IPC mechanism.
 */

int buildRandomStr(char *p) {
    char *build = p; // 
    if (p == NULL)
        return -1;

    for (int i = 0; i < STR_LEN; i++) {
        int r_char_ascii = rand() % 26;
        *(build++) = r_char_ascii + 97;
    }

    return 0;
}


int main()
{
    char *arrayOfStrings[50];
    for (int i = 0; i < 50; i++) {
        arrayOfStrings[i] = malloc(8 * sizeof(char)); // allocate 8 bytes for every string
        buildRandomStr(*(arrayOfStrings + i));
    }


    mkfifo("/tmp/fifo", LINUX_CODE); // creates the fifo
    char readBuffer[1000];
    char writeBuffer[1000];
    int writeIndex = 0;

    memset(readBuffer, 0, 1000);
    memset(writeBuffer, 0, 1000);

    int f;
    int wval;

    printf("[READY] P1\n");
    while (1) {
        f = open("/tmp/fifo", O_WRONLY);
        if (f < 0) {
            printf("[ERROR] Cannot write to FIFO.\n");
        }
        else { // writing the message in FIFO
            snprintf(writeBuffer, 100, "%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n", writeIndex, *(arrayOfStrings + writeIndex),
                writeIndex + 2, *(arrayOfStrings + writeIndex + 2), writeIndex + 1, *(arrayOfStrings + writeIndex + 1),
                writeIndex + 3, *(arrayOfStrings + writeIndex + 3), writeIndex + 4, *(arrayOfStrings + writeIndex + 4));
            
            
            printf("I sent:\n%s", writeBuffer);
            wval = write(f, writeBuffer, sizeof(writeBuffer));
            printf("[STATUS] Message has been written\n");

            close(f);
            f = open("/tmp/fifo", O_RDONLY);
            if (f  < 0) {
                printf("[ERROR] Cannot read FIFO");
            }

            read(f, readBuffer, 1000);
            close(f);

            printf("Received Data: %s\n", readBuffer);
            if (atoi(readBuffer) == writeIndex + 4) {
                writeIndex += 5;
            }
            else if (atoi(readBuffer) != writeIndex + 4) {
                printf("[Failure in data stream]");
            };

            if (writeIndex == 50) { // i.e the limit is reached
                break;
            }
        }
    };

    printf("[END] P1\n");
    unlink("/tmp/fifo"); // destroy the FIFO
    return 0;
}