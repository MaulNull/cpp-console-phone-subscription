#ifndef PHONE_SUBSCRIPTION_H
#define PHONE_SUBSCRIPTION_H

#include "constants.h"

struct date
{
    int day;
    int month;
    int year;
};

struct period
{
    int hours;
    int minutes;
    int seconds;
};

struct phone_subscription
{
    char number[MAX_STRING_SIZE];
    date dt;
    period start;
    period tm;
    char tariff[MAX_STRING_SIZE];
    double pay;
};

#endif
