#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "../../button/button.h"
#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../motor/motor.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void buttonHandlerTask(void* pvParameters);

#endif