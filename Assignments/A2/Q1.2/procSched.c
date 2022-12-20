#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NANOS_PER_SEC 1000000000L

// TODO: Remove any commented code before submitting file

char* countTime(struct timespec start, struct timespec end);



void createProc() {
    // for calculating times
    struct timespec startTime1, startTime2, startTime3;
    struct timespec endTime1, endTime2, endTime3;

    int proc1_id;
    int proc2_id;
    int proc3_id;

    clock_gettime(CLOCK_REALTIME, &startTime1);

    pid_t forkType1 = fork();





    if (forkType1 == -1) {
        printf("Error in using fork() in fn createProc\n");
        exit(1);
    }
    else if (forkType1 == 0) { // for child proc
        struct sched_param sp1;
        sp1.sched_priority = (sched_get_priority_min(SCHED_OTHER) + sched_get_priority_max(SCHED_OTHER)) / 2;
        
        proc1_id = getpid();
        sched_setscheduler(proc1_id, SCHED_OTHER, &sp1); // won't work on non-Linux devices
        execl("./scripts/s1.sh", NULL);
    }
    else {  // for parent proc
        clock_gettime(CLOCK_REALTIME, &startTime2);
        pid_t forkType2 = fork();
        if (forkType2 == -1) {
            printf("Error in forkType2\n");
            exit(1);
        }
        else if (forkType2 == 0) {
            struct sched_param sp2;
            sp2.sched_priority = (sched_get_priority_min(SCHED_RR) + sched_get_priority_max(SCHED_RR)) / 2;
            
            proc2_id = getpid();
            sched_setscheduler(proc2_id, SCHED_RR, &sp2); // won't work on non-Linux devices
            execl("./scripts/s2.sh", NULL);

        }
        else {
            clock_gettime(CLOCK_REALTIME, &startTime3); 
            pid_t forkType3 = fork();
            if (forkType3 == -1) {
                printf("Error in forkType3\n");
                exit(1);
            }
            else if (forkType3 == 0) {
                struct sched_param sp3;
                sp3.sched_priority = (sched_get_priority_min(SCHED_FIFO) + sched_get_priority_max(SCHED_FIFO)) / 2;
                
                proc2_id = getpid();
                sched_setscheduler(proc2_id, SCHED_RR, &sp3); // won't work on non-Linux devices
                execl("./scripts/s3.sh", NULL);
            }  
            else {
                int n = 3;
                while (n != 0) {
                    long pid = wait(NULL);
                    if (pid == forkType3) {
                        printf("Fork 1\n");
                        n--;
                        clock_gettime(CLOCK_REALTIME, &endTime1);
                    }
                    else if (pid == forkType2) {
                        printf("Fork 2\n");
                        n--;
                        clock_gettime(CLOCK_REALTIME, &endTime2);
                    }
                    else if (pid == forkType1) {
                        printf("Fork 3\n");
                        n--;
                        clock_gettime(CLOCK_REALTIME, &endTime3);
                    }

                }

            }
        }
    }

    printf("Time taken by Process A: %s\n", countTime(startTime1, endTime1));
    printf("Time taken by Process B: %s\n", countTime(startTime2, endTime2));
    printf("Time taken by Process C: %s\n", countTime(startTime3, endTime3));
}


char* countTime(struct timespec start, struct timespec end) {
    int timeTakenInSeconds = end.tv_sec - start.tv_sec;
    int timeTakenInNanoSeconds = end.tv_nsec - start.tv_nsec;
    if (timeTakenInNanoSeconds < 0) {
        long int nanoSecondsPerSecond = pow(10, 9);
        timeTakenInNanoSeconds = timeTakenInNanoSeconds + nanoSecondsPerSecond;
        timeTakenInSeconds -= 1;
    }
    char *returnValue = (char *)malloc(100 * sizeof(char));
    sprintf(returnValue, "%d.%d", timeTakenInSeconds, timeTakenInNanoSeconds);
    return returnValue;
}





int main() {
    createProc();    

    return 0;
}
