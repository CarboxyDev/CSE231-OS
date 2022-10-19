#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printString(char string[]) {

    for (int i=0; i < 1000; i++) {
        char chr = string[i];
        if (chr == '\0') {
            break;
        }
        printf("%c",chr);

    }

}



int main() {

    char stringArr[1000];
    int i = 0;

    printf("Enter string to reverse: ");
    while (1) { 
        char chr = fgetc(stdin);
        if (chr == '\n') {
            stringArr[i] = '\0';
            break;
        }
        stringArr[i] = chr;
        i++;
    }

    printf("Entered string: ");
    printString(stringArr);


    printf("\n");
    return 0;
}