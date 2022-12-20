#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>

#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1000
#define LINUX_CODE 06666


/**
 * This is P1 using Sockets IPC mechanism.
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


void startSocket() {
    char *arrayOfStrings[STR_COUNT];
    for (int i = 0; i < STR_COUNT; i++) {
        arrayOfStrings[i] = malloc(8 * sizeof(char)); // allocate 8 bytes for every string
        buildRandomStr(*(arrayOfStrings + i));
    }

    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];

    memset(readBuffer, 0, BUFFER_SIZE);
    memset(writeBuffer, 0, BUFFER_SIZE);

    struct sockaddr_un socketServer;
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);


    if ((sock < 0)) {
        printf("[ERROR] Could not open the socket. \n");
        return;
    }

    socketServer.sun_family = AF_UNIX;
    strcpy(socketServer.sun_path, "server");

    int socketAddrSize = sizeof(struct sockaddr_un);
    int socketBind = bind(sock, (struct sockaddr *)&socketServer, socketAddrSize);
    
    int socketListen = listen(sock, 5);

    printf("[READY] P1 using Socket\n");
    int messageSock = accept(sock, 0, 0);
    
    int writeMsg;
    int writeIndex;
    writeIndex = 0;

    while (1 == 1) {
        snprintf(writeBuffer, 128, "%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n%d -> %s\n",
            writeIndex, *(arrayOfStrings + writeIndex), writeIndex + 1, *(arrayOfStrings + writeIndex + 1),
            writeIndex + 2, *(arrayOfStrings + writeIndex + 2), writeIndex + 3, *(arrayOfStrings + writeIndex + 3),
            writeIndex + 4, *(arrayOfStrings + writeIndex + 4));

        printf("[INFO] Data sent by P1:\n%s", writeBuffer);
        writeMsg = write(messageSock, writeBuffer, BUFFER_SIZE);
        printf("[STATUS] Message has been written\n");

        read(messageSock, readBuffer, BUFFER_SIZE);
        printf("Received Data from P2: %s\n", readBuffer);
        
        int recvData = atoi(readBuffer);
        if ((writeIndex + 4) == recvData) {
            writeIndex += 5;
        }
        else if ((writeIndex + 4) != recvData) {
            printf("[Failure in socket stream]");
        };

        if (writeIndex >= 50) { // i.e the limit is reached
            break;
        }
    };

    printf("[END] P1\n");
    close(messageSock);
    close(sock);
    unlink("server");
}



int main() {

    clock_t start = clock();
    startSocket();
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by Socket: %f seconds\n", timeTaken);

    return 0;
}