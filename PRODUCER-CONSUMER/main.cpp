#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "buffer.h"

using namespace std;

void producer(int id) {
    while (true) {
        Record r;

        r.day = rand() % 30 + 1;
        r.month = rand() % 12 + 1;
        r.year = 16;
        r.storeID = id;
        r.regNum = rand() % 6 + 1;
        r.amount = (rand() % 100000) / 100.0;

        insertItem(r);

        if (isDone()) break;

        this_thread::sleep_for(chrono::milliseconds(rand()%35 + 5));
    }
}

void consumer(int id) {
    float localTotal = 0;

    while (true) {
        Record r;

        if (!removeItem(r)) {
            break;
        }

        localTotal += r.amount;
    }

    cout << "Consumer" << id << " total: " << localTotal << endl;
}


int main() {
    srand(time(0));

    initBuffer(10);

    int p = 5, c = 5;

    vector<thread> producers, consumers;

    for (int i = 0; i < p; i++) {
        producers.emplace_back(producer, i+1);
    }

    for (int i = 0; i < c; i++) {
        consumers.emplace_back(consumer, i+1);
    }

    for (auto &t : producers) t.join();
    for (auto &t : consumers) t.join();

    destroyBuffer();

    return 0;

}