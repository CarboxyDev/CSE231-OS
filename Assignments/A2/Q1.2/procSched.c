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

void createProc() {
    int proc1_id;
    int proc2_id;
    int proc3_id;
    pid_t forkType1 = fork();


    if (forkType1 == -1) {
        printf("Error in using fork() in fn createProc\n");
        exit(1);
    }
    else if (forkType1 == 0) { // for child proc
        struct sched_param sp1;
        sp1.sched_priority = (sched_get_priority_min(SCHED_OTHER) + sched_get_priority_max(SCHED_OTHER)) / 2;
        
        proc1_id = getpid();
        //sched_setscheduler(proc1_id, SCHED_OTHER, &sp1); // won't work on non-Linux devices
        execl("./scripts/s1.sh", NULL);
    }
    else {  // for parent proc
        waitpid(proc1_id, NULL, 0);

        pid_t forkType2 = fork();
        if (forkType2 == -1) {
            printf("Error in forkType2\n");
            exit(1);
        }
        else if (forkType2 == 0) {
            struct sched_param sp2;
            sp2.sched_priority = (sched_get_priority_min(SCHED_RR) + sched_get_priority_max(SCHED_RR)) / 2;
            
            proc2_id = getpid();
            //sched_setscheduler(proc2_id, SCHED_RR, &sp2); // won't work on non-Linux devices
            execl("./scripts/s2.sh", NULL);

        }
        else {
            waitpid(proc2_id, NULL, 0);

            pid_t forkType3 = fork();
            if (forkType3 == -1) {
                printf("Error in forkType3\n");
                exit(1);
            }
            else if (forkType3 == 0) {
                struct sched_param sp3;
                sp3.sched_priority = (sched_get_priority_min(SCHED_FIFO) + sched_get_priority_max(SCHED_FIFO)) / 2;
                
                proc2_id = getpid();
                //sched_setscheduler(proc2_id, SCHED_RR, &sp3); // won't work on non-Linux devices
                execl("./scripts/s3.sh", NULL);
            }  
            else {
                waitpid(proc3_id, NULL, 0);
            }
        }
    }
}





int main() {
    createProc();    


    return 0;
}
