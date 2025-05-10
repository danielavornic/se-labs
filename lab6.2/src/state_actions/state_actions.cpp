#include "state_actions.h"
#include "../config.h"

void enterEastGreen()
{
    clearAllLeds();

    setLed(LED_DIRECTION_EAST, LED_COLOR_GREEN, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}

void enterEastYellow()
{
    clearAllLeds();
    setLed(LED_DIRECTION_EAST, LED_COLOR_YELLOW, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}

void enterNorthGreen()
{
    clearAllLeds();
    setLed(LED_DIRECTION_NORTH, LED_COLOR_GREEN, HIGH);
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
}

void enterNorthYellow()
{
    clearAllLeds();
    setLed(LED_DIRECTION_NORTH, LED_COLOR_YELLOW, HIGH);
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
}

void enterAllRed()
{
    clearAllLeds();
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}