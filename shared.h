// shared.h
#ifndef SHARED_H
#define SHARED_H

#define SHARED_MEM_NAME "/shared_buffer"  // Shared memory name
#define SEM_MUTEX_NAME "/sem_mutex"       // Mutex semaphore for critical section
#define SEM_EMPTY_NAME "/sem_empty"       // Semaphore for empty slots
#define SEM_FULL_NAME  "/sem_full"        // Semaphore for filled slots
#define MAX_ITEMS 2                       // Table size

#endif  // SHARED_H
