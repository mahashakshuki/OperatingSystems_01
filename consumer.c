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

    // Open shared memory
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    shared_data = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Open semaphores
    sem_t *empty = sem_open("/empty", 0);
    sem_t *full = sem_open("/full", 0);
    sem_t *mutex = sem_open("/mutex", 0);

    for (int i = 0; i < 10; i++) {
        sem_wait(full);
        sem_wait(mutex);

        // Consume item at "out" index
        int item = shared_data->buffer[shared_data->out];
        printf("Consumer consumed: %d from index %d\n", item, shared_data->out);
        shared_data->out = (shared_data->out + 1) % BUFFER_SIZE;  // Circular buffer

        sem_post(mutex);
        sem_post(empty);

        sleep(2);
    }

    // Cleanup
    sem_close(empty);
    sem_close(full);
    sem_close(mutex);
    munmap(shared_data, sizeof(SharedData));
    close(shm_fd);

    return 0;
}
