/*
 *  This file will be used to make a binary ("rm") for the unix-shell program
 *  The created binary will allow the shell to use the rm command (following the POSIX standard while missing many common features)
 *  The rm command will be used to primarily delete files but also remove folders recursively using some special flags
 *  Supported Flags: -v, -i
 *  Supported Edge cases:
 *      1. Handle using the rm command on directories (illegal!)
 *      2. Handle using invalid file names as arguments
 * 
 *  TODO: None
 */


#include <stdio.h>
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
                printf("rm: Unable to remove the file\n");
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "-v") == 0) { // -v flag (verbose)
        if (access(argv[1], F_OK) != 0) { // file does not exist
            printf("rm: No such file\n");
        }
        else if (!checkFile(argv[1])) {
            printf("rm: %s is a directory\n", argv[1]);
        }
        else {
            if (remove(argv[1]) == 0) { // successful remove operation
                printf("Removed %s\n", argv[1]);
            }
            else {
                printf("rm: Unable to remove the file\n");
            }
        }
    }
    else if (argc == 2 && strcmp(argv[0], "-i") == 0) { // -i flag (seek confirmation before proceeding)
        if (access(argv[1], F_OK) != 0) { // file does not exist
            printf("rm: No such file\n");
        }
        else if (!checkFile(argv[1])) {
            printf("rm: %s is a directory\n", argv[1]);
        }
        else {
            printf("Remove %s? [y/n]", argv[1]);
            char choice[100];
            scanf("%s", choice);

            if (strcmp(choice,"y") == 0 || strcmp(choice, "yes") == 0) {
                if (remove(argv[1]) == 0) { // successful remove operation
                }
                else {
                    printf("rm: Unable to remove the file\n");
                }
            }
        }
    }
    else {
        printf("rm: Invalid format\n");
    }
    return 0;

}
