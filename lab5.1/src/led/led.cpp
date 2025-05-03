#include "led.h"

void initLED()
{
    pinMode(LED_PIN, OUTPUT);
}

void setLED(bool state)
{
    digitalWrite(LED_PIN, state ? HIGH : LOW);
}