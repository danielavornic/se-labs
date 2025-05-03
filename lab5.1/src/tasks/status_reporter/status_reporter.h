#ifndef STATUS_REPORTER_H
#define STATUS_REPORTER_H

#include "../../config/config.h"
#include "../../globals/globals.h"
#include "../../led/led.h"
#include <Arduino_FreeRTOS.h>
#include <stdio.h>

void statusReporterTask(void* pvParameters);

#endif