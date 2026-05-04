#include <iostream>
#include <fstream>
#include <vector>
#include "scheduler.h"

using namespace std;


/**
 * Vector that reads input (arrival and burst times)
 * and returns the processes for that input.
 */
vector<Process> readInput(string filename) {
    ifstream file(filename);
    vector<Process> processes;

    int arrival, burst;
    int id = 1;

    while (file >> arrival >> burst) {
        processes.push_back({id++, arrival, burst, 0, 0});
    }

    return processes;
}


/**
 * Main function that reads input from a sample text file
 * and outputs a choice for the user to make (FIFO or SJF algorithm).
 * Also outputs the statistics for the algorithms being executed.
 */
int main () {
    vector<Process> processes = readInput("input.txt");

    int choice;
    cout << "Choose Scheduling Algorithm:\n";
    cout << "1. FIFO\n";
    cout << "2. SJF\n";
    cin >> choice;

    if (choice == 1) {
        runFIFO(processes);
    }
    else {
        runSJF(processes);
    }

    calculateStats(processes);

    return 0;
}