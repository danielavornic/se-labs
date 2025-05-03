#ifndef STATUS_REPORTER_H
#define STATUS_REPORTER_H

#include "../../globals/globals.h"
#include <Arduino_FreeRTOS.h>
#include <stdio.h>

void statusReporterTask(void* pvParameters);

#endif