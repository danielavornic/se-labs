#include "joystick.h"
#include "../config/config.h"
#include "../conversion/conversion.h"

void initJoystick() {
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(JOYSTICK_BTN_PIN, INPUT_PULLUP);
}

JoystickData getJoystickData() {
    JoystickData data;
    
    int rawX = analogRead(JOYSTICK_X_PIN);
    int rawY = analogRead(JOYSTICK_Y_PIN);
    
    float xVoltage = adcToVoltage(rawX, VREF, ADC_RESOLUTION);
    float yVoltage = adcToVoltage(rawY, VREF, ADC_RESOLUTION);
    
    data.x_angle = voltageToAngle(xVoltage, VREF, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);
    data.y_angle = voltageToAngle(yVoltage, VREF, JOYSTICK_MIN_ANGLE, JOYSTICK_MAX_ANGLE);
    
    data.button = !digitalRead(JOYSTICK_BTN_PIN);
    
    return data;
} 