#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define unsigned long int lu


lu factorial(lu n) {
    if (n == 1 ){
        return 1;
    }
    return n * factorial(n - 1);
}




int main() {
    printf("%lu\n", factorial(3));
    int f = fork();

    if (f == -1) { // fork fail
        printf("Fork failed. No child proc was created.");
    }
    else if (f == 0) { // child process 
        printf("[Execute] Child proc %d\n", getpid());
        sleep(2);
    }
    else if (f > 0) { // parent process
        printf("[WAIT] Parent proc %d\n", f);
        wait(NULL);
        printf("[EXECUTE] Parent proc %d\n", f);
    }





    
    printf("[END] Proc %d", getpid());
    printf("\n");
    return 0;
}