#ifndef CODE_HANDLER_H
#define CODE_HANDLER_H

#include <Arduino.h>

#define MAX_CODE_LENGTH 4
#define VALID_CODE "823#"

void passcodeInit();
void readPasscode();

#endif