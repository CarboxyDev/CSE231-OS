#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void* threadFunction(){


    return NULL;
}



int main(){

    printf("[!] Starting Dual Threads Program\n");    

    pthread_t threadId;
    printf("Thread hasn't been created yet\n");

    pthread_create(&threadId, NULL, threadFunction, NULL);
    pthread_join(threadId, NULL);

    printf("Thread created now.\n");


    return 0;
}