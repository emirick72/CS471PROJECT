#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int start;
    int finish;
}

void runFIFO(vector<Process>& processes);
void runSJF(vector<Process>& processes);
void calculateStats(vector<Process>& processes);


#endif;