#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define SHM_NAME "/shared_memory"
#define BUFFER_SIZE 2

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedData;

int main() {
    int shm_fd;
    SharedData *shared_data;

    // Create shared memory
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedData));
    shared_data = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize shared data
    shared_data->in = 0;
    shared_data->out = 0;

    // Create semaphores
    sem_t *empty = sem_open("/empty", O_CREAT, 0666, BUFFER_SIZE);
    sem_t *full = sem_open("/full", O_CREAT, 0666, 0);
    sem_t *mutex = sem_open("/mutex", O_CREAT, 0666, 1);

//for loop for the numbers : 
    for (int i = 1; i <= 10; i++)
 {
        sem_wait(empty);
        sem_wait(mutex);

 // Produce item at "in" index
        shared_data->buffer[shared_data->in] = i;
        printf("Producer produced: %d at index %d\n", i, shared_data->in);
        shared_data->in = (shared_data->in + 1) % BUFFER_SIZE;  // Circular buffer

        sem_post(mutex);
        sem_post(full);

        sleep(1);
    }

    // Cleanup to aviod crashing 
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);

    return 0;
}
