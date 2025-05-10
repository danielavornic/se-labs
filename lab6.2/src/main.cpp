#include "button/button.h"
#include "config.h"
#include "fsm/fsm.h"
#include "led/led.h"
#include "serial_comm/serial_comm.h"
#include <Arduino.h>

void setup()
{
    initSerial();
    initButton();
    initLeds();
    initFSM();
}

void loop()
{
    updateFSM();
    delay(10);
}