/*
 *  This file will be used to make a binary ("cat") for the unix-shell program
 *  The created binary will allow the shell to use the cat command (following the POSIX standard while missing many common features)
 *  The cat command is used to view the contents of a file (or multiple files, concatenated) specified by the user
 *  Supported Flags: -b, -n
 *  Supported Edge cases: 1. Disallow using cat on folders  2. TBA
 */


#include <stdio.h>
#include <sys/stat.h>


// check if the file is a directory or not.
int checkFile(char filePath[]) {
    struct stat file;
    stat(filePath, &file);
    return S_ISREG(file.st_mode); // returns 0 if given path is a directory and not a file
} 



int main(int argc, char* argv[]) {
    if (argc == 0) { // Not sure if this is the correct way to handle this case as the mac terminal just seems to hang whenever cat is called with no args
        printf("Error: You need to give some file(s) as argument\n");
    }
    else if (argc == 1) { // Handle a single file
        
        if (!checkFile(argv[0])) {
            printf("cat: %s is a directory\n", argv[0]);
        }
        else {
            FILE *file;
            file = fopen(argv[0], "r");

            if (file == NULL) {
                printf("cat: Error: Invalid file name provided\n");
            }
            else
            {
                while (1)
                {
                    char chr = fgetc(file);
                    if (chr == EOF)
                    {
                        break;
                    }
                    printf("%c", chr);
                }
            }

            printf("\n");
        }

    }
    
    return 0;
}