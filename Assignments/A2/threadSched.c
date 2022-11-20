#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


void* countA(void* vargptr) {
    printf("[Count A]");
    for (int i=0; i < pow(2,32); i++) {
        // do no computation
    }
    return NULL;
}

void* countB(void* vargptr) {
    printf("[Count B]");
    return NULL;
}

void* countC(void* vargptr) {
    printf("[Count C]");
    return NULL;
}



int main() {




    return 0;
}