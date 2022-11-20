#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>


void* countA(void* vargptr) {
    printf("[Count A]");
    unsigned long i;
    for (i=1; i < 4294967296; i++) {
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

    /*
    pthread_attr_t threadA_attr;
    struct sched_param threadA_param;
    pthread_attr_init (&threadA_attr);
    pthread_attr_getschedparam (&threadA_attr, &threadA_param);
    */
    struct sched_param threadA_schedParam;
    threadA_schedParam.sched_priority = 0;
    pthread_setschedparam(threadA, SCHED_OTHER, &threadA_schedParam);


	pthread_create(&threadA, NULL, countA , NULL);
    pthread_join(threadA, NULL);




    return 0;
}