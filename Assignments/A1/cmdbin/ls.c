/*
 *  This file will be used to make a binary ("ls") for the unix-shell program
 *  The created binary will allow the shell to use the ls command (following the POSIX standard while missing many common features)
 *  The ls command is primarily used to view the contents of the shell's current working directory
 *  Supported Flags: -a, -l
 *  Supported Edge cases:
 *      1. Allow usage of ls on directories relative to the current directory
 *      2. Handle the case where the ls'd directory does not exist
 * 
 *  TODO: Implement the edge cases
 */


#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if (argc == 0 || ((argc == 1) && (strcmp(argv[0],"-a") == 0 || strcmp(argv[0], "-l") == 0))) {
        char currentDir[PATH_MAX];

        if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
            struct dirent *dir;
            DIR *dirNav = opendir(currentDir);
            if (dirNav == 0) {
                printf("Error in running ls on this directory");
                return 0;
            }
            
            dir = readdir(dirNav);
            while (dir != NULL) {
                if (argc == 1) { // this means that a flag exists like -a / -l
                    if (strcmp(argv[0], "-a") != 0) { // -a flag is NOT chosen 
                        if (dir->d_name[0] == '.') {
                            dir = readdir(dirNav);
                            continue; // basically skip the dotfiles/hidden files
                        } 
                        
                    }
                    printf("%s   ", dir->d_name); // print the dir name

                    if (strcmp(argv[0],"-l") == 0) { // -l flag is chosen
                        printf("\n");
                    }
                }
                else if (argc == 0) {
                    if (dir->d_name[0] == '.') {
                        dir = readdir(dirNav);
                        continue; // skip the dotfiles/hidden 
                    }
                    printf("%s   ", dir->d_name); // print the dir name
                }
                dir = readdir(dirNav);
            }
            printf("\n");

        }
    }

    return 0;

}