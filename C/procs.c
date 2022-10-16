#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long int lu;

lu factorial(lu n) {
    if (n == 1 ){
        return 1;
    }
    return n * factorial(n - 1);
}




int main() {

    int f = fork();

    if (f == -1) { // fork fail
        printf("Fork failed. No child proc was created.");
    }
    else if (f == 0) { // child process 
        printf("[Execute] Child proc %d\n", getpid());
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