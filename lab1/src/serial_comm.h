#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <Arduino.h>
#include <stdio.h>

// speed for serial communication
// 9600 is standard speed for Arduino
#define SERIAL_BAUD_RATE 9600
#define MAX_MESSAGE_LENGTH 7

void serialInit();
void serialProcess();

#endif