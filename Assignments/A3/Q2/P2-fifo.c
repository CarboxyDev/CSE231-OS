#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/un.h>

/**
 * This is P2 using FIFO IPC mechanism.
 */

int main() {
    int sock, wval, fd;
    int iterator = 10;
    char readBuffer[1000];
    char writeBuffer[1000];

    memset(readBuffer, 0, 1000);
    memset(writeBuffer, 0, 1000);


    int maxind = -1;
    int prev_maxind = -1;


    printf("[READY] P2\n");
    while (iterator) {
        if ((fd = open("/tmp/fifo", O_RDONLY)) < 0)
        {
            perror("Do not run p2 first");
        }
        readToBuf(fd, readBuffer, 1000);

        printf("I received:\n%s", readBuffer);

        sscanf(readBuffer, "%d%*s", &maxind);
        if (prev_maxind != maxind)
        {
            --iterator;
            prev_maxind = maxind;
        }

        close(fd);
        if ((fd = open("/tmp/fifo", O_WRONLY)) < 0)
            perror("fifo not writable\n");

        snprintf(writeBuffer, 8, "%d", maxind + 4);
        printf("send val = %s\n", writeBuffer);
        if ((wval = write(fd, writeBuffer, 1000)) < 0)
            perror("writing on stream socket\n");
        close(fd);
    }

    printf("TERMINATING P2, TASK COMPLETED.\n");
    close(fd);
}