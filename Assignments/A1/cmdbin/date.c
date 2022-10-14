#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char* argv[]) {


    if (argc == 0) {
        char formatTime[1000];
        time_t currentTime;
        time(&currentTime);
        strcpy(formatTime, ctime(&currentTime));

        printf("Local Time: %s", formatTime);
    }
    else if (argc == 1 && strcmp(argv[0], "-u") == 0) {
        // -u flag is encountered
        char utcTime[1000];
        time_t utc;

        struct tm* t;
        time(&utc);
        t = gmtime(&utc);
        printf("UTC Time: %s", asctime(t));

    }

    else if (argc == 1 && strcmp(argv[0],"-R") == 0) {
        // -R flag is encountered. Print date/time in RFC 5322 format
        char formatTime[1000];
        time_t currentTime;
        time(&currentTime);
        strcpy(formatTime, ctime(&currentTime));

        strtok(formatTime, "\n"); // remove the trailing newline character from the localdate
        printf("Local Time: %s +0530\n", formatTime);
    }

    return 0;

}