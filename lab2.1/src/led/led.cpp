#include "led.h"
#include <Arduino.h>

void initLeds()
{
    pinMode(LED_1_PIN, OUTPUT);
    pinMode(BLINKING_LED_PIN, OUTPUT);
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(BLINKING_LED_PIN, LOW);
}

void setLedState(int pin, bool state)
{
    digitalWrite(pin, state ? HIGH : LOW);
}

void toggleLed(int pin)
{
    digitalWrite(pin, !digitalRead(pin));
}
