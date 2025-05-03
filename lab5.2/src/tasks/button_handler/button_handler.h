#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "../../button/button.h"
#include "../../globals/globals.h"
#include "../../motor/motor.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define BUTTON_SETPOINT_CHANGE_UNITS 5

void buttonHandlerTask(void* pvParameters);

#endif