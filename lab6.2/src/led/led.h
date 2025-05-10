#ifndef LED_H
#define LED_H

#include "../config.h"
#include <Arduino.h>

// LED direction enum
typedef enum {
    LED_DIRECTION_EAST,
    LED_DIRECTION_NORTH
} LedDirection;

// LED color enum
typedef enum {
    LED_COLOR_RED,
    LED_COLOR_YELLOW,
    LED_COLOR_GREEN
} LedColor;

// Initialize all LED pins
void initLeds();

// Set a specific LED state
void setLed(LedDirection direction, LedColor color, bool state);

// Turn off all LEDs for a direction
void clearDirectionLeds(LedDirection direction);

// Turn off all LEDs
void clearAllLeds();

// Get pin number for a specific LED
uint8_t getLedPin(LedDirection direction, LedColor color);

#endif
