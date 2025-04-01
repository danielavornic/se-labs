#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <Arduino.h>
#include <stdio.h>

#define SERIAL_BAUD_RATE 9600

void initSerial();
void printRelayStatus();
#endif