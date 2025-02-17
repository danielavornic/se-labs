#include "led_control.h"
#include "serial_comm.h"
#include <Arduino.h>

void setup()
{
    serialInit();
    ledInit();
}

void loop()
{
    serialProcess();
}