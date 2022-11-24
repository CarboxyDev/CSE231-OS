#include <linux/kernel.h>

// refernce: https://brennan.io/2016/11/14/kernel-dev-ep3/

SYSCALL_DEFINE3(kernel_2d_memcpy, unsigned long int, elemCount, long*, source, long*, dest) {

    long memHold[1]; // holds some temporary memory for every iteration of copying
    int memChunkSize = 8;
    long* destPtrAlt = dest; // need to create to act like a pseudo-dest variable in copytouser
    for (unsigned long long int i=0; i < elemCount; i++) {
        if (__copy_from_user(memHold, source++ , memChunkSize) != 0) {
            return -EFAULT;
        }
        if (__copy_to_user(destPtrAlt++, memHold, memChunkSize) != 0) {
            return -EFAULT;
        }
    }
    // runs on fully successful copying of data
    return (long) dest;


}