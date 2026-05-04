#include "scheduler.h"
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Function that runs the FIFO (first in, first out)
 * scheduling algorithm.
 * Simulates a non-preemptive CPU scheduling algorithm.
 * Takes a list of processes (arrival and burst times) as input.
 * The first process that arrives is the first one to execute.
 */
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


/**
 * Function that runs the SJF (shortest job first)
 * scheduling algorithm.
 * Simulates a non-preemptive CPU scheduling algorithm.
 * Takes a list of processes (arrival and burst times) as input.
 * `processes` vector is updated with result.
 */
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

/**
 * Function that calculates and outputs the statistics of each
 * scheduling algorithm (FIFO and SJF).
 * Each output is in a sample output file.
 */
void calculateStats(vector<Process>& processes) {
    double totalWait = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;
    double totalBurst = 0;

    int startTime = processes[0].arrival;;
    int endTime = 0;

    for (auto &p : processes) {
        int wait = p.start - p.arrival;
        int turnaround = p.finish - p.arrival;
        int response = wait;

        totalWait += wait;
        totalTurnaround += turnaround;
        totalResponse += response;
        totalBurst += p.burst;

        endTime = max(endTime, p.finish);
    }

    int n = processes.size();
    double elapsed = endTime - startTime;

    cout << "\n--- Statistics ---\n";
    cout << "Processes: " << n << endl;
    cout << "Total elasped time: " << elapsed << endl;
    cout << "Throughput: " << (double)n / elapsed << endl;
    cout << "CPU Utilization: " << (totalBurst / elapsed) * 100 << "%" << endl;
    cout << "Avg Waiting Time: " << totalWait / n << endl;
    cout << "Avg Turnaround Time: " << totalTurnaround / n << endl;
    cout << "Avg Response Time: " << totalResponse / n << endl;
}