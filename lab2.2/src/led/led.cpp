#include "led.h"
#include "../config/config.h"

void initLEDs()
{
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}

void setLED1(bool state)
{
    digitalWrite(LED1_PIN, state ? HIGH : LOW);
}

void setLED2(bool state)
{
    digitalWrite(LED2_PIN, state ? HIGH : LOW);
}