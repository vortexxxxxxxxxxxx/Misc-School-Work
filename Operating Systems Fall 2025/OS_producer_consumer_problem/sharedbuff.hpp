#ifndef SHARED_BUFFER
#define SHARED_BUFFER

#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <thread>
#include <iostream>

const int BUF_LENGTH = 2;
struct SharedData {
    sem_t avail_slots, filled_slots, lock;
    int buffer[BUF_LENGTH];
};

#endif
