/*
 *  This file will be used to make a binary ("mkdir") for the unix-shell program
 *  The created binary will allow the shell to use the mkdir command (following the POSIX standard while missing many common features)
 *  The mkdir command will generally create a new directory for the user
 *  Supported Flags: -v, -p
 *  Supported Edge cases:
 *      1. Create multiple directories at once
 *      2. Error message when requested directory already exists
 *  
 *  TODO: Implement -p flag and edge case 1
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>


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
            printf("mkdir: Directory already exists\n");
        }
    }
    else if (argc == 2 && strcmp(argv[0], "-v") == 0) { // -v flag (verbose)
         struct stat s;
        if (stat(argv[1], &s) == -1) { 
            mkdir(argv[1], 0700);
            printf("Created directory %s\n", argv[1]);
        }
        else {
            printf("mkdir: Directory already exists\n");
        }
    }


    return 0;

}