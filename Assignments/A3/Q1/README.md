### Functions used for functionality

Some important functions used for concurrency purposes are:
    sem_init()
    sem_wait()
    sem_post()
    pthread_mutex_init()
    pthead_mutex_join()
    pthread_mutex_destroy()

### Explanation

There were 2 ways of handling the synchronization problem.
1. Ordering of resource requests
-> This involved using mutex locks provided by pthread for solving the concurrency problems. Here, deadlock can still occur in case all the philosophers pick the left fork at the same time. It would result in a stalemate/deadlock situation and no one will be able to eat.

2. Using semaphores
-> This involved using semaphores instead of mutex locks where the semaphore variable is shared and only one of it exists. Processes (Philosophers) can signal to others when they've stopped eating or when they want to eat using functions definde in <semaphore.h> header.

