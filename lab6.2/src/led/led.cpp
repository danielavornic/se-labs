#include "led.h"

uint8_t getLedPin(LedDirection direction, LedColor color)
{
    switch (direction) {
    case LED_DIRECTION_EAST:
        switch (color) {
        case LED_COLOR_RED:
            return EAST_RED_PIN;
        case LED_COLOR_YELLOW:
            return EAST_YELLOW_PIN;
        case LED_COLOR_GREEN:
            return EAST_GREEN_PIN;
        }
        break;
    case LED_DIRECTION_NORTH:
        switch (color) {
        case LED_COLOR_RED:
            return NORTH_RED_PIN;
        case LED_COLOR_YELLOW:
            return NORTH_YELLOW_PIN;
        case LED_COLOR_GREEN:
            return NORTH_GREEN_PIN;
        }
        break;
    }
    return 0;
}

void initLeds()
{
    pinMode(EAST_RED_PIN, OUTPUT);
    pinMode(EAST_YELLOW_PIN, OUTPUT);
    pinMode(EAST_GREEN_PIN, OUTPUT);

    pinMode(NORTH_RED_PIN, OUTPUT);
    pinMode(NORTH_YELLOW_PIN, OUTPUT);
    pinMode(NORTH_GREEN_PIN, OUTPUT);

    clearAllLeds();
}

void setLed(LedDirection direction, LedColor color, bool state)
{
    uint8_t pin = getLedPin(direction, color);
    digitalWrite(pin, state ? HIGH : LOW);
}

void clearDirectionLeds(LedDirection direction)
{
    setLed(direction, LED_COLOR_RED, LOW);
    setLed(direction, LED_COLOR_YELLOW, LOW);
    setLed(direction, LED_COLOR_GREEN, LOW);
}

void clearAllLeds()
{
    clearDirectionLeds(LED_DIRECTION_EAST);
    clearDirectionLeds(LED_DIRECTION_NORTH);
}
