#ifndef TIMING_H
#define TIMING_H

#include <Arduino.h>

#define UPDATE_INTERVAL 100

void initTiming();
bool isUpdateDue();
void markUpdateTime();

#endif
