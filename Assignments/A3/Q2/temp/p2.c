#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>

#define SHM_KEY 0x1234 // Shared memory key
#define SHM_SIZE 1024   // Size of shared memory segment
#define GROUP_SIZE 5    // Number of integers received in each group

int main() {
  // Create a shared memory segment
  int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
  if (shmid < 0) {
    perror("Error creating shared memory segment");
    exit(1);
  }

  // Attach to the shared memory segment
  int* shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == (int*)-1) {
    perror("Error attaching to shared memory segment");
    exit(1);
  }

  // Keep track of the current index in the array
  int index = 0;

  while (index < 50) {
    // Wait for a group of integers to be sent from P1
    while (shared_memory[GROUP_SIZE] == index) {
      sleep(1);
    }

    // Print the received integers and their IDs
    printf("Received integers:\n");
    for (int i = 0; i < GROUP_SIZE; i++) {
      printf("ID: %d, Value: %d\n", index + i, shared_memory[i]);
    }

    // Send acknowledgement to P1
    shared_memory[GROUP_SIZE] = index + GROUP_SIZE;

    // Update the current index
    index = shared_memory[GROUP_SIZE];
  }

  // Detach from the shared memory segment
  if (shmdt(shared_memory) == -1) {
    perror("Error detaching from shared memory segment");
    exit(1);
  }

  return 0;
}

