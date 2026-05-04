#ifndef BUFFER_H
#define BUFFER_H

#include <queue>

struct Record {
    int day, month, year;
    int storeID;
    int regNum;
    float amount;
};


void initBuffer(int size);
void insertItem(const Record& item);
void removeItem(Record& item);
void destroyBuffer();

bool isDone();

#endif