#include "led_control.h"
#include "serial_comm.h"
#include <Arduino.h>

void setup()
{
    serialInit();
    ledInit();

    printf("enter command (led on/led off):\n");
}

void loop()
{
    serialProcess();
}