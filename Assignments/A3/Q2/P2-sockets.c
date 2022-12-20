#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>


#define STR_LEN 8
#define STR_COUNT 50
#define ASCII_START 97
#define BUFFER_SIZE 1000
#define LINUX_CODE 06666
#define CHAR_COUNT 8
#define ITER_COUNT 10


int main() {
    int iterator = 10;
    char readBuffer[BUFFER_SIZE];
    char writeBuffer[BUFFER_SIZE];

    memset(readBuffer, 0, BUFFER_SIZE);
    memset(writeBuffer, 0, BUFFER_SIZE);

    struct sockaddr_un socketServer;

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if ((sock < 0)) {
        printf("[ERROR] Could not open the socket.\n");
        return -1;
    }

    socketServer.sun_family = AF_UNIX;
    strcpy(socketServer.sun_path, "server");

    int socketConnect = connect(sock, (struct sockaddr *)&socketServer, sizeof(struct sockaddr_un));

    if (socketConnect < 0) {
        perror("[ERROR] Could not connect to the socket. Weird.\n");
        close(sock);
        return -1;
    }

    printf("[READY] P1\n");

    int indexLimitMax = -1;
    int indexLimitMax_prev = -1;

    int writeMsg;

    while (iterator) {
        read(sock, readBuffer, BUFFER_SIZE);

        printf("[INFO] Data received from P1:\n%s", readBuffer);

        sscanf(readBuffer, "%d%*s", &indexLimitMax);

        if (indexLimitMax_prev != indexLimitMax) {
            indexLimitMax_prev = indexLimitMax;
            iterator -= 1;
        };

        int newIndexLimitMax = indexLimitMax + 4;

        snprintf(writeBuffer, CHAR_COUNT, "%d", newIndexLimitMax);
        printf("[STATUS] Message has been sent\n");
        printf("Message sent: %s\n", writeBuffer);

        writeMsg = write(sock, writeBuffer, BUFFER_SIZE);

    }

    printf("[END] P2\n");
    close(sock);
}