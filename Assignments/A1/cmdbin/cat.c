/*
 *  This file will be used to make a binary ("cat") for the unix-shell program
 *  The created binary will allow the shell to use the cat command (following the POSIX standard while missing many common features)
 *  The cat command is used to view the contents of a file (or multiple files, concatenated) specified by the user
 *  Supported Flags: -b, -n
 *  Supported Edge cases:
 *      1. Handle using cat command on directories (illegal!)
 *      2. Handle invalid file names
 *      3. Handle the case when no argument is given with the command
 *  
 *  TODO: Handle multiple files in input
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


// check if the file is a directory or not.
int checkFile(char filePath[]) {
    struct stat file;
    stat(filePath, &file);
    return S_ISREG(file.st_mode); // returns 0 if given path is a directory and not a file
} 



int main(int argc, char* argv[]) {
    if (argc == 0) { // Not sure if this is the correct way to handle this case as the mac terminal just seems to hang whenever cat is called with no args
        printf("cat: You need to give some file as argument\n");
    }
    else if (argc == 1) { // Handle a single file
        if (access(argv[0], F_OK) != 0) { // file does not exist
            printf("cat: No such file or directory\n");
        }
        else if (!checkFile(argv[0])) {
            printf("cat: %s is a directory\n", argv[0]);
        }
        else {
            FILE *file;
            file = fopen(argv[0], "r");

            if (file == NULL) {
                printf("cat: Error: Invalid file name provided\n");
            }
            else {
                while (1) {
                    char chr = fgetc(file);
                    if (chr == EOF) {
                        break;
                    }
                    printf("%c", chr);
                }
            }

            printf("\n");
        }

    }
    else if (argc >= 2 && strcmp(argv[0], "-n") == 0) {
        if (access(argv[1], F_OK) != 0) { // file does not exist
            printf("cat: No such file or directory\n");
        }
        else if (!checkFile(argv[1])) {
            printf("cat: %s is a directory\n", argv[1]);
        }
        else {
            FILE *file;
            file = fopen(argv[1], "r");
            char lineBuffer[512];

            if (file == NULL) {
                printf("cat: Error: Invalid file name provided\n");
            }
            else {
                int lineNumber = 1;
                while (fgets(lineBuffer, 512, file) != 0) {
                    printf(" %d %s", lineNumber, lineBuffer);
                    lineNumber++;
                }
            }
            printf("\n");
        }
    }
    else if (argc >= 2 && strcmp(argv[0], "-b") == 0) {
        if (access(argv[1], F_OK) != 0) { // file does not exist
            printf("cat: No such file or directory\n");
        }
        else if (!checkFile(argv[1])) {
            printf("cat: %s is a directory\n", argv[1]);
        }
        else {
            FILE *file;
            file = fopen(argv[1], "r");
            char lineBuffer[512];

            if (file == NULL) {
                printf("cat: Error: Invalid file name provided\n");
            }
            else {
                int lineNumber = 1;
                while (fgets(lineBuffer, 512, file) != 0) {
                    if (strcmp(lineBuffer, "\n") == 0) { // the line is a blank line
                        printf("\n");
                    }
                    else {
                        printf(" %d %s", lineNumber, lineBuffer);
                        lineNumber++;
                    }
                }
            }
            printf("\n");
        }
    }


    return 0;
}