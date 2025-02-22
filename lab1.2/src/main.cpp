#include "keypad/keypad_control.h"
#include "lcd/lcd_control.h"
#include "led/led_control.h"
#include "passcode/passcode.h"

void setup()
{
    ledInit();
    lcdInit();
    keypadInit();
    passcodeInit();
}

void loop()
{
    readPasscode();
}