/*
 *  This file will be used to make a binary ("rm") for the unix-shell program
 *  The created binary will allow the shell to use the rm command (following the POSIX standard while missing many common features)
 *  The rm command will be used to primarily delete files but also remove folders recursively using some special flags
 *  Supported Flags: -v, -i
 *  Supported Edge cases:
 *      1. Handle using the rm command on directories (illegal!)
 *      2. Handle using invalid file names as arguments
 * 
 *  TODO: Implement the command
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

// check if the file is a directory or not.
int checkFile(char filePath[]) {
    struct stat file;
    stat(filePath, &file);
    return S_ISREG(file.st_mode); // returns 0 if given path is a directory and not a file
}


int main(int argc, char *argv[]) {
    if (argc == 0) { 
        printf("rm: You need to give some file as input\n");
    }
    else if (argc == 1) { // delete a single file
        if (access(argv[0], F_OK) != 0) { // file does not exist
            printf("rm: No such file\n");
        }
        else if (!checkFile(argv[0])) {
            printf("rm: %s is a directory\n", argv[0]);
        }
        else {
            if (remove(argv[0]) == 0) { // successful remove operation

            }
            else {
                printf("rm: Unable to remove the file");
            }
        }
    }

    return 0;

}
