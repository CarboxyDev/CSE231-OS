#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <time.h>

#define NANOS_PER_SEC 1000000000L

static double showClock(struct timespec clockStartTime, struct timespec clockStopTime) {
    double measure = ( clockStopTime.tv_sec - clockStartTime.tv_sec ) + (float)( clockStopTime.tv_nsec - clockStartTime.tv_nsec ) / NANOS_PER_SEC;
    return measure;

}


void* countA(void* vargptr) {
    struct timespec clockStartTime;
    double measure;

    unsigned long long int i;
    int didClockStart = clock_gettime(CLOCK_REALTIME, &clockStartTime);
    if (didClockStart == -1) {
        printf("Error in clock_gettime() at start of count fn.");
        exit(1);
    };

    for (i=1; i < 4294967296; i++) {};

    struct timespec clockStopTime;
    int didClockStop = clock_gettime(CLOCK_REALTIME, &clockStopTime);
    if (didClockStop == -1) {
        printf("Error in clock_gettime() at end of count fn.");
        exit(1);
    };

    measure = ( clockStopTime.tv_sec - clockStartTime.tv_sec ) + (float)( clockStopTime.tv_nsec - clockStartTime.tv_nsec ) / NANOS_PER_SEC;

    printf("[!] Thread A -> Clock time: %lf s\n", measure);

    return NULL;
}

void* countB(void* vargptr) {
    struct timespec clockStartTime;
    double measure;

    unsigned long long int i;
    int didClockStart = clock_gettime(CLOCK_REALTIME, &clockStartTime);
    if (didClockStart == -1) {
        printf("Error in clock_gettime() at start of count fn.");
        exit(1);
    };

    for (i=1; i < 4294967296; i++) {};

    struct timespec clockStopTime;
    int didClockStop = clock_gettime(CLOCK_REALTIME, &clockStopTime);
    if (didClockStop == -1) {
        printf("Error in clock_gettime() at end of count fn.");
        exit(1);
    };

    measure = ( clockStopTime.tv_sec - clockStartTime.tv_sec ) + (float)( clockStopTime.tv_nsec - clockStartTime.tv_nsec ) / NANOS_PER_SEC;

    printf("[!] Thread B -> Clock time: %lf s\n", measure);

    return NULL;
}

void* countC(void* vargptr) {
    struct timespec clockStartTime;
    double measure;

    unsigned long long int i;
    int didClockStart = clock_gettime(CLOCK_REALTIME, &clockStartTime);
    if (didClockStart == -1) {
        printf("Error in clock_gettime() at start of count fn.");
        exit(1);
    };

    for (i=1; i < 4294967296; i++) {};

    struct timespec clockStopTime;
    int didClockStop = clock_gettime(CLOCK_REALTIME, &clockStopTime);
    if (didClockStop == -1) {
        printf("Error in clock_gettime() at end of count fn.");
        exit(1);
    };

    measure = ( clockStopTime.tv_sec - clockStartTime.tv_sec ) + (float)( clockStopTime.tv_nsec - clockStartTime.tv_nsec ) / NANOS_PER_SEC;

    printf("[!] Thread C -> Clock time: %lf s\n", measure);

    return NULL;
}



int main() {
    printf("[!] Start program\n");

    int SCHED_RR_minPriority = sched_get_priority_min(SCHED_RR);
    int SCHED_RR_maxPriority = sched_get_priority_max(SCHED_RR);
    int SCHED_FIFO_minPriority = sched_get_priority_min(SCHED_FIFO);
    int SCHED_FIFO_maxPriority = sched_get_priority_max(SCHED_FIFO);

    int threadB_priorityBreak = (SCHED_RR_maxPriority - SCHED_RR_minPriority) / 10;
    int threadC_priorityBreak = (SCHED_FIFO_maxPriority - SCHED_FIFO_minPriority) / 10;
    /*
    FILE *filePointer;
    filePointer = fopen("threadSchedData.txt", "w");

    if (filePointer == NULL) {
        printf("Error in file handling. Please try again.\n");
        exit(1);
    }*/

    for (int i = 0; i < 10; i++) {
        
        printf("[ITERATION %d]\n", i + 1);
        // THREAD A    
        pthread_t threadA;
        pthread_attr_t attrA;
        struct sched_param threadA_param;
        threadA_param.sched_priority = 0;
        if (pthread_attr_init(&attrA) != 0) {
            printf("Error in initializing thread A.\n");
        }
        pthread_attr_setschedpolicy(&attrA, SCHED_OTHER);
        pthread_attr_setschedparam(&attrA, &threadA_param);

        // THREAD B
        pthread_t threadB;

        pthread_attr_t attrB;
        struct sched_param threadB_param;
        threadB_param.sched_priority = SCHED_RR_minPriority + i * threadB_priorityBreak;
        if (pthread_attr_init(&attrB) != 0) {
            printf("Error in initializing thread B.\n");
        }
        pthread_attr_setschedpolicy(&attrB, SCHED_RR);
        pthread_attr_setschedparam(&attrB, &threadB_param);


        // THREAD C
        pthread_t threadC;

        pthread_attr_t attrC;
        struct sched_param threadC_param;
        threadC_param.sched_priority = SCHED_FIFO_minPriority + i * threadC_priorityBreak;
        if (pthread_attr_init(&attrC) != 0) {
            printf("Error in initializing thread C.\n");
        }
        pthread_attr_setschedpolicy(&attrC, SCHED_FIFO);
        pthread_attr_setschedparam(&attrC, &threadC_param);

        // in testing, A -> slowest, B & C -> similar time 
        pthread_attr_setinheritsched(&attrA, PTHREAD_EXPLICIT_SCHED); // where attr is the attr of thread
        pthread_attr_setinheritsched(&attrB, PTHREAD_EXPLICIT_SCHED); // where attr is the attr of thread
        pthread_attr_setinheritsched(&attrC, PTHREAD_EXPLICIT_SCHED); // where attr is the attr of thread  


        // Create the threads
        pthread_create(&threadA, NULL, countA , NULL);
        pthread_create(&threadB, NULL, countB , NULL);
        pthread_create(&threadC, NULL, countC , NULL); 


        pthread_join(threadA, NULL);
        pthread_join(threadB, NULL);
        pthread_join(threadC, NULL);

        pthread_attr_destroy(&attrA);
        pthread_attr_destroy(&attrB);
        pthread_attr_destroy(&attrC);

        printf("-----------------------------------------\n\n");
    }

    //fclose(filePointer);
    


    return 0;
}