#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
 *  This program uses mutex locks for the Phil Dining problem  
*/

pthread_mutex_t forks[5];
pthread_t phil[5];

void think(int x) {
    printf("Philosopher %d is THINKING\n", x);
}

void eat(int x) {
    int pos = 1 + x;

    think(x);
    pthread_mutex_lock(&forks[x]);
    pthread_mutex_lock(&forks[pos % 5]);
    printf("Philosopher %d has started EATING\n", x);

    sleep(2);

    pthread_mutex_unlock(&forks[x]);
    pthread_mutex_unlock(&forks[pos % 5]);
    printf("Philosopher %d FINISHED EATING\n", x);
} 



int main(){
    while (1 == 1) {
        for (int i=0; i < 5; i++) {
            int tryInit = pthread_mutex_init(&forks[i], NULL);
            if (tryInit == -1) {
                printf("[!] Unable to use mutex\n");
                return 0;
            }
        };

        for (int i=0; i < 5; i++) {
            int tryCreate = pthread_create(&phil[i], NULL, (void *) eat, (int *) i);
            if (tryCreate != 0) {
                printf("[!] Unable to create thread\n");
                return 0;
            }
        };

        for (int i=0; i < 5; i++) {
            int tryJoin = pthread_join(phil[i], NULL);
            if (tryJoin != 0) {
                printf("[!] Unable to join thread\n");
                return 0;
            }
        }

        for (int i=0; i < 5; i++) {
            int tryDestroy = pthread_mutex_destroy(&forks[i]);
            if (tryDestroy != 0) {
                return 0;
            }
        }

    };

    return 0;
}