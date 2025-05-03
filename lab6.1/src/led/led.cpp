#include "led.h"

void initLed()
{
    pinMode(LED_PIN, OUTPUT);
    ledOff();
}

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
}

void ledOff()
{
    digitalWrite(LED_PIN, LOW);
}

void ledToggle()
{
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
