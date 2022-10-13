#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char* argv[]) {

    time_t currentTime;
    time(&currentTime);

    // check for flags here
    char formatTime[1000];
    strcpy(formatTime, ctime(&currentTime));

    printf("%s", formatTime);

    return 0;

}