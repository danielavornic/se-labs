#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <Arduino.h>
#include <stdio.h>

// constants
// baud - speed of communication, 9600 - standard speed for Arduino
#define SERIAL_BAUD_RATE 9600
// max length of message
#define MAX_MESSAGE_LENGTH 64 // for scanf

void serialInit();
void serialProcess();
int serialGetChar();
void serialPutChar(char c);
void serialPrintString(const char* str);

#endif