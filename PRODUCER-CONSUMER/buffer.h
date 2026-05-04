#ifndef BUFFER_H
#define BUFFER_H

#include <queue>

extern int totalProduced;
extern const int MAX_ITEMS;

/**Initialize variables */
struct Record {
    int day, month, year;
    int storeID;
    int regNum;
    float amount;
};

/**Initialize functions */
void initBuffer(int size);
void insertItem(const Record& item);
bool removeItem(Record& item);
void destroyBuffer();

bool isDone();

#endif