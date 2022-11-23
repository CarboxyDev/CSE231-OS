#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <time.h>

void createProc() {
    pid_t forkType = fork();

    if (forkType == -1) {
        printf("Error in using fork() in fn createProc\n");
        exit(1);
    }
    else if (forkType == 0) { // for child proc
        // do some stuff for the child proc
    }
    else { 
        wait(NULL);
    
    }
}





int main() {
    createProc();    


    return 0;
}
