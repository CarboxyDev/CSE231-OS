#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <time.h>

#define NANOS_PER_SEC 1000000000L


void* countA(void* vargptr) {
    clock_t t;
    t = clock();

    unsigned long i;
    for (i=1; i < 4294967296; i++) {
    }

    t = clock() - t;
    double clockTimeThreadA = ((double)t)/ CLOCKS_PER_SEC;
    printf("[!] Thread A - Clock time: %lf s\n", clockTimeThreadA);

    return NULL;
}

void* countB(void* vargptr) {
    clock_t t;
    t = clock();

    unsigned long i;
    for (i=1; i < 4294967296; i++) {
    }

    t = clock() - t;
    double clockTimeThreadB = ((double)t)/ CLOCKS_PER_SEC;
    printf("[!] Thread B - Clock time: %lf s\n", clockTimeThreadB);

    return NULL;
}

void* countC(void* vargptr) {
    clock_t t;
    t = clock();

    unsigned long i;
    for (i=1; i < 4294967296; i++) {
    }

    t = clock() - t;
    double clockTimeThreadC = ((double)t)/ CLOCKS_PER_SEC;
    printf("[!] Thread C - Clock time: %lf s\n", clockTimeThreadC);

    return NULL;
}



int main() {
    printf("[!] Start program\n");

    // THREAD A    
    pthread_t threadA;

    struct sched_param threadA_schedParam;
    threadA_schedParam.sched_priority = 0;
    pthread_setschedparam(threadA, SCHED_OTHER, &threadA_schedParam);

	pthread_create(&threadA, NULL, countA , NULL);
    pthread_join(threadA, NULL);


    // THREAD B
    pthread_t threadB;

    struct sched_param threadB_schedParam;
    threadB_schedParam.sched_priority = 0;
    pthread_setschedparam(threadB, SCHED_RR, &threadB_schedParam);

	pthread_create(&threadB, NULL, countB , NULL);
    pthread_join(threadB, NULL);


    // THREAD C
    pthread_t threadC;

    struct sched_param threadC_schedParam;
    threadC_schedParam.sched_priority = 0;
    pthread_setschedparam(threadC, SCHED_FIFO, &threadC_schedParam);

	pthread_create(&threadC, NULL, countC , NULL);
    pthread_join(threadC, NULL);




    return 0;
}