#include "processing.h"
int periodToSeconds(const phone_subscription* p) {
    return p->tm.hours * 3600 + p->tm.minutes * 60 + p->tm.seconds;
}
double process(phone_subscription* array[], int size)
{
    double totalCost = 0.0;
    double totalSeconds = 0.0;

    for (int i = 0; i < size; i++) {
        totalCost += array[i] -> pay;
        totalSeconds += periodToSeconds(array[i]);
    }
    return totalCost/totalSeconds;
}