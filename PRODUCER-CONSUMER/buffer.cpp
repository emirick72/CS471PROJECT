#include "buffer.h"
#include <semaphore.h>
#include <mutex>

using namespace std;

queue<Record> buffer;
int BUFFER_SIZE;

sem_t emptySlots;
sem_t fullSlots;
mutex mtx;

int totalProduced = 0;
const int MAX_ITEMS = 1000;

bool doneProducing = false;


/**Function to initialize the buffer */
void initBuffer(int size) {
    BUFFER_SIZE = size;
    sem_init(&emptySlots, 0, size);
    sem_init(&fullSlots, 0, 0);
}

/**Function to insert items into the buffer (using mutex lock) */
void insertItem(const Record& item) {
    sem_wait(&emptySlots);
    mtx.lock();

    if (totalProduced < MAX_ITEMS) {
        buffer.push(item);
        totalProduced++;

        if (totalProduced == MAX_ITEMS) {
            doneProducing = true;
        }
    }

    mtx.unlock();
    sem_post(&fullSlots);
}


/**Function to remove items from the buffer (using mutex lock) */
bool removeItem(Record& item) {
    sem_wait(&fullSlots);
    mtx.lock();

    if (buffer.empty() && doneProducing) {
        mtx.unlock();
        sem_post(&fullSlots);
        return false;
    }

    if (!buffer.empty()) {
        item = buffer.front();
        buffer.pop();
    }

    mtx.unlock();
    sem_post(&emptySlots);
    return true;
}

/**Function to destroy the buffer when finished */
void destroyBuffer() {
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
}

/**Function for when done producing records */
bool isDone() {
    lock_guard<mutex> lock(mtx);
    return doneProducing;
}