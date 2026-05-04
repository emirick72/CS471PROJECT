#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <cstdlib>
#include <chrono>


#include "buffer.h"

using namespace std;

vector<float> storeTotals(20, 0);
vector<float> monthTotals(13, 0);
float globalTotal = 0;

void producer(int id) {
    while (true) {

        if (totalProduced >= MAX_ITEMS) break;

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

        storeTotals[r.storeID] += r.amount;
        monthTotals[r.month] += r.amount;
        globalTotal += r.amount;
    }

    cout << "Consumer " << id << " total: " << localTotal << endl;
}





int main() {

    srand(time(0));

    initBuffer(10);

    vector<thread> producers;
    vector<thread> consumers;

    int p = 2;
    int c = 2;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < p; i++) {
        producers.emplace_back(producer, i + 1);
    }

    for (int i = 0; i < c; i++) {
        consumers.emplace_back(consumer, i + 1);
    }

    for (auto &t : producers) {
        t.join();
    }

    for (auto &t : consumers) {
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "\nProduced: " << totalProduced << "\n" << endl;

    cout << "Simulation time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";

    cout << "Global Total: " << globalTotal << endl;

    
    return 0;

}