#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/kernel.h>



int main() {
    
    double matrix[3][3] = {
        {1.234, 2.345, 3.456},
        {2.345, 3.456, 4.567},
        {3.456, 4.567, 5.678}
    };

    double* memDest;
    memDest = malloc(sizeof(matrix)); // allocate sufficient memory for the destination memory where we have to copy the matrix to

    /* 
    syscall format:
        syscall(<syscall number>, <amount of elements to copy>, <source mem>, <destination mem>);
        kernel_2d_memcpy takes in order -> number of elements, source memory, destination memory
    */

   int syscallNumber = 451;
   int elemsCopyCount = 3 * 3; // amount of elements to copy -> number of elements in the matrix to copy
   printf("Using a syscall with number ", syscall(syscallNumber, elemsCopyCount, matrix, memDest));


    for (int i=0; i < elemsCopyCount; i++) {
        printf("%.12lf\n", (*memCloneAddr++));
    }


    return 0;
}