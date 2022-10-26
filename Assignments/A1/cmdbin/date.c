/*
 *  This file will be used to make a binary ("date") for the unix-shell program
 *  The created binary will allow the shell to use the date command (following the POSIX standard while missing many common features)
 *  The date command will be used to fetch the user's date on their Operating System
 *  Supported Flags: -u, -R
 *  Supported Edge cases:
 *      1. Handle cases of invalid usage
 *      2. TBD
 * 
 *  TODO: Implement the remaining edge case
 */


#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char* argv[]) {
    if (argc == 0) { // when no arguments or flags are provided
        char formatTime[1000];
        time_t currentTime;
        time(&currentTime);
        strcpy(formatTime, ctime(&currentTime));

        printf("Local Time: %s", formatTime);
    }
    else if (argc == 1 && strcmp(argv[0], "-u") == 0) { // -u flag. Print datetime in UTC
        char utcTime[1000];
        time_t utc;

        struct tm* t;
        time(&utc);
        t = gmtime(&utc);
        printf("UTC Time: %s", asctime(t));
    }
    else if (argc == 1 && strcmp(argv[0],"-R") == 0) { // -R flag. Print datetime in RFC 5322 format
        char formatTime[1000];
        time_t currentTime;
        time(&currentTime);
        strcpy(formatTime, ctime(&currentTime));

        strtok(formatTime, "\n"); // remove the trailing newline character from the localdate
        printf("Local Time: %s +0530\n", formatTime);
    }
    else {
        printf("date: Invalid usage\n");
    }


    return 0;

}