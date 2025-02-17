#include "led_control.h"

static bool ledState = false;

void ledInit()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
    ledState = true;
}

void ledOff()
{
    digitalWrite(LED_PIN, LOW);
    ledState = false;
}

bool ledGetState()
{
    return ledState;
}