#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    printf("Execute ls.c\n");

    if (argc == 0 || ((argc == 1) && (strcmp(argv[0],"-a") == 0 || strcmp(argv[0], "-l") == 0))) {
        char currentDir[PATH_MAX];
        printf("Args -> %d\n", argc);

        if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
            printf("Dir exists!\n");
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
                            continue; // basically skip the dotfiles/hidden files
                        } 
                        
                    }
                    printf("%s\t", dir->d_name); // print the dir name

                    if (strcmp(argv[0],"-l") == 0) { // -l flag is chosen
                        printf("\n");
                    }
                }

                dir = readdir(dirNav);
            }

        }
    }


}