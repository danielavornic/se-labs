#include "led_control.h"

void ledInit()
{
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
}

void ledGreenOn()
{
    digitalWrite(LED_GREEN_PIN, HIGH);
}

void ledGreenOff()
{
    digitalWrite(LED_GREEN_PIN, LOW);
}

void ledRedOn()
{
    digitalWrite(LED_RED_PIN, HIGH);
}

void ledRedOff()
{
    digitalWrite(LED_RED_PIN, LOW);
}