/*
 *  This file will be used to make a binary ("date") for the unix-shell program
 *  The created binary will allow the shell to use the date command (following the POSIX standard while missing many common features)
 *  The date command will be used to fetch the user's date on their Operating System
 *  Supported Flags: -u, -r, -R
 *  Supported Edge cases:
 *      1. Handle cases of invalid usage of date command
 *      2. Handle case where -r is used on a file that does not exist
 *      3. Handle case where -r is used without any argument
 * 
 *  TODO: None
 */


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    if (argc >= 2) {
        int isThreadBased = 0;
        int i = 0;
        while (1) {
            if (argv[i] == NULL) {
                if (strcmp(argv[i - 1], "!t") == 0) {
                    isThreadBased = 1;
                };
                break;
            };

            i++;
        };

        if (isThreadBased) {
            argc -= 2;
            char* new[1000];

            i = 0;
            int c = 0;
            while (1) {
                if (argv[i] == NULL) {
                    new[c] = NULL;
                    break;
                }
                else if (strcmp(argv[i], "!t") == 0) {
                    new[c] = NULL;
                    break;
                }
                else if (i == 0) {
                    i++;
                    continue;
                }
                strcpy(new[c], argv[i]);
                i++;
                c++;
            };
            
            int x = 0;
            while (1) {
                if (new[x] == NULL) {
                    argv[x] = NULL;
                    break;
                }
                strcpy(argv[x], new[x]);
                x++;
            };
        }

    };

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
    else if ((argc == 1 || argc == 2) && strcmp(argv[0],"-r") == 0) { // -r flag. Print last modification date of a particular file
        if (argc == 2) {
            if (access(argv[1], F_OK) != 0) { // file does not exist
                printf("date: Specified file does not exist\n");
                return 0;
            }

            char filePath[PATH_MAX];
            strcpy(filePath, argv[1]);
            struct stat fileInfo;
            stat(filePath, &fileInfo);
            char *lmt = ctime(&fileInfo.st_mtime);

            printf("Last modified time for %s: %s", filePath, lmt);
        }
        else if (argc == 1){
            printf("date: Specify a file name along with the -r flag\n");
        }

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