#include "lcd_control.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);
FILE lcdOutput = { 0 };

int lcdPutchar(char c, FILE* stream)
{
    if (c == '\f') {
        lcd.clear();
    } else if (c == '\n') {
        // move to second line
        lcd.setCursor(0, 1);
    } else {
        lcd.write(c);
    }

    return 0;
}

void lcdInit()
{
    // initialize lcd
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);

    fdev_setup_stream(&lcdOutput, lcdPutchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcdOutput;
}
