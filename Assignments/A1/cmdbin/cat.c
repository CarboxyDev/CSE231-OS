/*
 *  This file will be used to make a binary ("cat") for the unix-shell program
 *  The created binary will allow the shell to use the cat command (following the POSIX standard while missing many common features)
 *  The cat command is used to view the contents of a file (or multiple files, concatenated) specified by the user
 *  Supported Flags: -b, -n
 *  Supported Edge cases:
 *      1. Handle using cat command on directories (illegal!)
 *      2. Handle invalid file names as arguments
 *      3. Handle the case when no argument is given with the command
 *      4. Handle multiple files as input
 *  
 *  TODO: None
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




    if (argc == 0) { 
        printf("cat: No files as input provided\n");
    }
    else if (argc >= 1 && !(strcmp(argv[0], "-n") == 0 || strcmp(argv[0], "-b") == 0)) {
        int i = 0;

        while (1) {
            if (argv[i] == NULL) {
                break;
            }
            else if (access(argv[i], F_OK) != 0) { // file does not exist
                printf("cat: %s: No such file or directory\n", argv[i]);
                i++;
                continue;
            }
            else if (!checkFile(argv[i])) {
                printf("cat: %s: Is a directory\n", argv[i]);
                break;
            }
            else {
                FILE *file;
                file = fopen(argv[i], "r");

                if (file == NULL) {
                    printf("cat: %s: No such file or directory\n", argv[i]);
                    i++;
                    continue;
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
            }

            i++;
        }
    }
    else if (argc >= 2 && strcmp(argv[0], "-n") == 0) {
        int i = 1;

        while (1) {
            int lineNumber = 1;
            char lineBuffer[512];

            if (argv[i] == NULL) {
                break;
            }
            else if (access(argv[i], F_OK) != 0) { // file does not exist
                printf("cat: %s: No such file or directory\n", argv[i]);
                i++;
                continue;
            }
            else if (!checkFile(argv[i])) {
                printf("cat: %s: Is a directory\n", argv[i]);
                break;
            }
            else {
                FILE *file;
                file = fopen(argv[i], "r");

                if (file == NULL) {
                    printf("cat: %s: No such file or directory\n", argv[i]);
                    i++;
                    continue;
                }
                else {
                    while (fgets(lineBuffer, 512, file) != 0) {
                        printf(" %d %s", lineNumber, lineBuffer);
                        lineNumber++;
                    }
                }
            }

            i++;
        }
    }

    else if (argc >= 2 && strcmp(argv[0], "-b") == 0) {
        int i = 1;

        while (1) {
            int lineNumber = 1;
            char lineBuffer[512];

            if (argv[i] == NULL) {
                break;
            }
            else if (access(argv[i], F_OK) != 0) { // file does not exist
                printf("cat: %s: No such file or directory\n", argv[i]);
                i++;
                continue;
            }
            else if (!checkFile(argv[i])) {
                printf("cat: %s: Is a directory\n", argv[i]);
                break;
            }
            else {
                FILE *file;
                file = fopen(argv[i], "r");

                if (file == NULL) {
                    printf("cat: %s: No such file or directory\n", argv[i]);
                    i++;
                    continue;
                }
                else {
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
            }

            i++;
        }
    }

    return 0;
}