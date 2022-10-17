#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>




void* threadFunction(){

    FILE* fptr;
    fptr = fopen("mock.txt", "r");



    return NULL;
}



int main(){

    printf("[!] Starting Dual Threads Program\n");   

    // thread 1 
    pthread_t threadId;

    pthread_create(&threadId, NULL, threadFunction, NULL);
    pthread_join(threadId, NULL);

    printf("Thread 1 created now.\n");


    // thread 2
    pthread_t threadId_2;

    pthread_create(&threadId_2, NULL, threadFunction, NULL);
    pthread_join(threadId_2, NULL);

    printf("Thread 2 created now.\n");
    return 0;
}