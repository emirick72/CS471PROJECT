#include "scheduler.h"
#include <algorithm>
#include <iostream>

using namespace std;

void runFIFO(vector<Process>& processes) {
    sort(processes.begin(), processes.end(),
        [](Process a, Process b) {
            return a.arrival < b.arrival;
        }
    );

    int currentTime = 0;

    for (auto &p : processes) {
        if (currentTime < p.arrival) {
            currentTime = p.arrival;
        }

        p.start = currentTime;
        p.finish = currentTime + p.burst;

        currentTime = p.finish;
    }
}