/*
 *  This file will be used to make a binary ("mkdir") for the unix-shell program
 *  The created binary will allow the shell to use the mkdir command (following the POSIX standard while missing many common features)
 *  The mkdir command will generally create a new directory for the user
 *  Supported Flags: TBD
 *  Supported Edge cases: TBD
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) {

    if (argc == 1) { // create a single directory
        struct stat s;
        if (stat(argv[0], &s) == -1) { // directory does not already exist
            mkdir(argv[0], 0700); // finally create the directory
        }
        else { // directory already exists
            printf("mkdir: Directory already exists\n");
        }
    }


    return 0;
}