#include "state_actions.h"
#include "../config.h"

static unsigned long lastFlashToggleTime = 0;
static bool yellowLedsAreOn = false;

void enterEastGreen()
{
    clearAllLeds();
    setLed(LED_DIRECTION_EAST, LED_COLOR_GREEN, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}

void updateEastGreen() { }

void enterEastYellow()
{
    clearAllLeds();
    setLed(LED_DIRECTION_EAST, LED_COLOR_YELLOW, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}

void updateEastYellow() { }

void enterNorthGreen()
{
    clearAllLeds();
    setLed(LED_DIRECTION_NORTH, LED_COLOR_GREEN, HIGH);
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
}

void updateNorthGreen() { }

void enterNorthYellow()
{
    clearAllLeds();
    setLed(LED_DIRECTION_NORTH, LED_COLOR_YELLOW, HIGH);
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
}

void updateNorthYellow() { }

void enterAllRed()
{
    clearAllLeds();
    setLed(LED_DIRECTION_EAST, LED_COLOR_RED, HIGH);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_RED, HIGH);
}

void updateAllRed() { }

void enterFlashingYellow()
{
    clearAllLeds();
    yellowLedsAreOn = true;
    setLed(LED_DIRECTION_EAST, LED_COLOR_YELLOW, yellowLedsAreOn);
    setLed(LED_DIRECTION_NORTH, LED_COLOR_YELLOW, yellowLedsAreOn);
    lastFlashToggleTime = millis();
}

void updateFlashingYellow()
{
    if (millis() - lastFlashToggleTime >= FLASH_INTERVAL) {
        yellowLedsAreOn = !yellowLedsAreOn;
        setLed(LED_DIRECTION_EAST, LED_COLOR_YELLOW, yellowLedsAreOn);
        setLed(LED_DIRECTION_NORTH, LED_COLOR_YELLOW, yellowLedsAreOn);
        lastFlashToggleTime = millis();
    }
}