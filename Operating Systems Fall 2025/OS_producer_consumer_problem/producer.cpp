#include <thread>
#include <iostream>
#include "sharedbuff.hpp"

// producer runs on infinite loop like the consumer
void producer(SharedData* data) {
    while (true) {
        sem_wait(&data->avail_slots);
        sem_wait(&data->lock);

        int produced_sum = 0;
        for (int i = 0; i < BUF_LENGTH; i++) {
            data->buffer[i] = rand() % 100 + 1;
            produced_sum += data->buffer[i];
        }

        std::cout << "[*] Produced: " << produced_sum << std::endl;

        sem_post(&data->lock);
        sem_post(&data->filled_slots);  // signal when buffer has been filled by producer

        sleep(1);
    }
}

int main() {
    srand(time(0));

    // attempt creating shared memory buffer
    int shm_fd = shm_open("/shared_buffer", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Error: Failed to open shared memory." << std::endl;
        return 1;
    }

    // modify the size of the buffer
    ftruncate(shm_fd, sizeof(SharedData));
    if (shm_fd == -1) {
        std::cerr << "[-] Error: Failed to open (shm)shared_buffer." << std::endl;
        return 1;
    }

    // attempt mapping
    SharedData* data = (SharedData*) mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        std::cerr << "[-] Error: Failed to map shared memory." << std::endl;
        return 1;
    }

    // semaphores
    sem_init(&data->avail_slots, 1, BUF_LENGTH); // buffer is empty
    sem_init(&data->filled_slots, 1, 0);         // start of buffer is empty
    sem_init(&data->lock, 1, 1);                 // mutex is used for mutual-exclusion

    std::thread producer_thread(producer, data);
    producer_thread.join();

    return 0;
}
