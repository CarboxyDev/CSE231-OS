#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


void* countA(void* vargptr) {
    printf("[Count A]");
    unsigned long i = 1;
    for (int i=1; i < pow(2,32); i++) {
    }
    printf("\nFinished countA\n");
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
    printf("[!] Start program\n");
    pthread_t threadA;
	pthread_create(&threadA, NULL, countA , NULL);
    pthread_join(threadA, NULL);




    return 0;
}