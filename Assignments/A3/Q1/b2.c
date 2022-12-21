#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
 *  This program uses semaphores for the Phil Dining problem variation which has 2 bowls
*/

sem_t forks[5];
sem_t sauce_bowls[2];
sem_t phil;

void think(int x) {
    printf("Philosopher %d is THINKING\n", x);
}

void* eat(void* n) {
    int x = *(int *) n;
    int pos = 1 + x;

    sem_wait(&phil);
	sem_wait(&forks[x]);
	sem_wait(&forks[pos % 5]);
    sem_wait(&sauce_bowls[x % 2]);
    printf("Philosopher %d has started EATING\n", x);
	
    sleep(2);

    sem_post(&sauce_bowls[x % 2]);
	sem_post(&forks[pos % 5]);
	sem_post(&forks[x]);
	sem_post(&phil);
    printf("Philosopher %d has FINISHED eating\n", x);
}


int main() {
    printf("[!] Start execution\n");
    while (1 == 1) {
        pthread_t threads[5];
        int threadHold[5];
        int trySemInit = sem_init(&phil, 0, 4);

        for(int i=0; i < 5; i++) {
            int trySemInit2 = sem_init(&forks[i], 0, 1); // 2nd arg 0 indicates that the sem is being shared between threads
        }

        for(int i=0; i < 2; i++) {
            int trySemInit3 = sem_init(&sauce_bowls[i], 0, 1); // 2nd arg 0 indicates that the sem is being shared between threads
        }

        for(int i=0; i < 5; i++) {
            threadHold[i] = i;
            int tryCreate = pthread_create(&threads[i], NULL, (void *) eat, (void *)&threadHold[i]);

            if (tryCreate != 0) {
                printf("[!] Unable to create thread\n");
                return 0;
            }
        }

        for(int i=0; i < 5; i++) {
            int tryJoin = pthread_join(threads[i], NULL);

            if (tryJoin != 0) {
                printf("[!] Unable to join thread\n");
                return 0;
            }
        }
    };
    
    return 0;
}


