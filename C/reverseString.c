#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This program assumes that the maximum string size is 1000 characters */

void printString(char string[]) {

    for (int i=0; i < 1000; i++) {
        char chr = string[i];
        if (chr == '\0') {
            break;
        }
        printf("%c",chr);
    }
    printf("\n");
}


void reverseString(char string[], char* reversed) {

    int idx; // is the string length as well
    char newString[1000];

    for (int i=0; i < 1000; i++) {
        char chr = string[i];
        if (chr == '\0') {
            idx = i;
            break;
        }
    }
    
    int c = idx;
    for (int i=0; i < idx; i++) {
        if (c <= 0) {
            newString[idx] = '\0';
            break;
        }
        char chr = string[c - 1];
        newString[i] = chr;
        c--;
    }
  
    strcpy(reversed, newString);

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
    printf("Reversed string: ");
    char* rev;
    reverseString(stringArr, rev);
    printf("%s\n", rev);

    return 0;
}