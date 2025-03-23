#include "display.h"
#include <stdio.h>

void formatFloat(char* buffer, float value)
{
    int intPart = (int)value;
    int decPart = abs((int)(value * 100) % 100);
    sprintf(buffer, "%d.%02d", intPart, decPart);
}

void formatAngle(char* buffer, float angle)
{
    char floatStr[10];
    formatFloat(floatStr, angle);
    sprintf(buffer, "%s deg", floatStr);
}

void formatVoltage(char* buffer, float voltage)
{
    char floatStr[10];
    formatFloat(floatStr, voltage);
    sprintf(buffer, "%s V", floatStr);
}