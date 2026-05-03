#include <iostream>
#include <fstream>
#include <vector>
#include "scheduler.h"

using namespace std;

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