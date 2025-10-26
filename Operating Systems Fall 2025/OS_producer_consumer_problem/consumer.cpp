#include <thread>
#include <iostream>
#include "sharedbuff.hpp"

// thread target, the consumer runs in an infinite-loop meaning
// to kill the process we need to use external binaries such as:
// kill,pkill,killall,etc
void consumer(SharedData* data) {
    while (true) {
        sem_wait(&data->filled_slots);  // wait till the buffer is full
        sem_wait(&data->lock); // wait for access to the buffer

        int consumed_sum = 0;

        // iterate over the shared buffer
        for (int i = 0; i < BUF_LENGTH; ++i) {
            consumed_sum += data->buffer[i];
            data->buffer[i] = 0;
        }

        std::cout << "[*] Consumed: " << consumed_sum << std::endl;

        sem_post(&data->lock); // release the buffer
        sem_post(&data->avail_slots); // send a signal when the buffer is empty and on element consumption

        sleep(1); // sleep to give the CPU a breather
    }
}

int main() {
    srand(time(0));

    int shm_fd = shm_open("/shared_buffer", O_RDWR, 0666);
    
    if (shm_fd == -1) {
        std::cerr << "[-] Error: Failed to open (shm)shared_buffer." << std::endl;
        return 1;
    }

    // attempt to map the SharedData
    SharedData* data = (SharedData*) mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    if (data == MAP_FAILED) {
        std::cerr << "[-] Error: Failed to map shared memory." << std::endl;
        return 1;
    }

    // create the thread to consume buffer entries stuffed by producer
    std::thread consumer_thread(consumer, data);
    // halt program until the thread has finished its assigned task
    consumer_thread.join();

    return 0;
}
