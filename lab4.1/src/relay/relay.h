#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

void initRelay();
void setRelay(bool state);
bool getRelayState();

#endif