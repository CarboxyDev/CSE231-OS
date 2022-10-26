/*
 *  This file will be used to make a binary ("mkdir") for the unix-shell program
 *  The created binary will allow the shell to use the mkdir command (following the POSIX standard while missing many common features)
 *  The mkdir command will generally create a new directory for the user
 *  Supported Flags: -v, -p
 *  Supported Edge cases:
 *      1. Create multiple directories at once (without using any flags)
 *      2. Error message when requested directory already exists
 *  
 *  TODO: None
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc == 0) {
        printf("mkdir: You need to give something as input\n");
    }
    else if (argc == 1) { // create a single directory
        struct stat s;
        if (stat(argv[0], &s) == -1) { // directory does not already exist
            mkdir(argv[0], 0700); // finally create the directory
        }
        else { // directory already exists
            printf("mkdir: %s: Directory already exists\n", argv[0]);
        }
    }
    else if (argc == 2 && strcmp(argv[0], "-v") == 0) { // -v flag (verbose)
        struct stat s;
        if (stat(argv[1], &s) == -1) { 
            mkdir(argv[1], 0700);
            printf("Created directory %s\n", argv[1]);
        }
        else {
            printf("mkdir: %s: Directory already exists\n", argv[1]);
        }
    }
    else if (argc == 2 && strcmp(argv[0], "-p") == 0) { // -p flag (does not support creating multiple directories)
        char *token = strtok(argv[1], "/");
        char path[PATH_MAX];

        int i = 0;
        while (token != NULL) {
            char tempToken[1000] = "/";
            if (i == 0) {
                strcpy(tempToken, token);
            }
            else if (i != 0) {
                strcat(tempToken, token);
            }
            strcat(path, tempToken);
            if (token != NULL) {
                i++;
                struct stat s;
                if (stat(path, &s) == -1) {
                    mkdir(path, 0700);
                }
                else {
                    printf("mkdir: %s: Directory already exists\n", path);
                }
                token = strtok(NULL, "/");
            }
        }
    }
    else if (argc >= 2) { // create multiple directories w/o use of any flags
        int i = 0;
        while (1) {
            if (argv[i] == NULL) {
                break;
            }
            struct stat s;
            if (stat(argv[i], &s) == -1) {
                mkdir(argv[i], 0700);
            }
            else {
                printf("mkdir: %s: Directory already exists\n", argv[i]);
                i++;
                continue;
            }

            i++;
        }

    }

    return 0;

}