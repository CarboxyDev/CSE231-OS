#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SHM_KEY 0x1234 // Shared memory key
#define SHM_SIZE 1024   // Size of shared memory segment
#define NUM_INTS 50     // Number of integers to generate
#define GROUP_SIZE 5    // Number of integers to send in each group

int main() {
  // Create a shared memory segment
  int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
  if (shmid < 0) {
    perror("Error creating shared memory segment");
    exit(1);
  }
  printf("Start \n");

  // Attach to the shared memory segment
  int* shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == (int*)-1) {
    perror("Error attaching to shared memory segment");
    exit(1);
  }
  printf("Attach \n");

  // Generate an array of random integers
  int ints[NUM_INTS];
  srand(time(NULL)); // Seed the random number generator
  for (int i = 0; i < NUM_INTS; i++) {
    ints[i] = rand();
  }
  printf("Generate \n");

  // Keep track of the current index in the array
  int index = 0;

  while (index < NUM_INTS) {
    printf("sending... \n");
    // Send a group of integers to P2
    for (int i = 0; i < GROUP_SIZE; i++) {
      shared_memory[i] = ints[index + i];
    }

    // Send the IDs of the integers to P2
    shared_memory[GROUP_SIZE] = index;

    // Wait for acknowledgement from P2
    while (shared_memory[GROUP_SIZE] == index) {
      printf("waiting for ACK \n");
      sleep(1);
    }

    // Update the current index
    index = shared_memory[GROUP_SIZE];
  }

  // Detach from the shared memory segment
  if (shmdt(shared_memory) == -1) {
    perror("Error detaching from shared memory segment");
    exit(1);
  }
  printf("End \n");

  return 0;
}

