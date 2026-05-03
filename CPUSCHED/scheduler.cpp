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

void runSJF(vector<Process>& processes) {
    vector<Process> result;
    int currentTime = 0;

    while (result.size() < processes.size()) {
        vector<Process> ready;

        for (auto &p : processes) {
            bool alreadyDone = false;

            for (auto &r : result) {
                if (r.id == p.id) {
                    alreadyDone = true;
                }
            }

            if (!alreadyDone && p.arrival <= currentTime) {
                ready.push_back(p);
            }
        }

        if (ready.empty()) {
            currentTime++;
            continue;
        }

        sort(ready.begin(), ready.end(),
            [](Process a, Process b) {
                return a.burst < b.burst;
            }
        );
        
        Process p = ready[0];

        p.start = currentTime;
        p.finish = currentTime + p.burst;

        currentTime = p.finish;

        result.push_back(p);
    }

    processes = result;
}