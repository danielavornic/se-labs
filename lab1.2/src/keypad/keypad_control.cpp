#include "keypad_control.h"

static Keypad keypad(makeKeymap((char*)KEYS), (byte*)ROW_PINS, (byte*)COL_PINS, ROWS, COLS);
FILE keypadInput = { 0 };

void keypadInit()
{
    fdev_setup_stream(&keypadInput, NULL, keypadGetChar, _FDEV_SETUP_READ);
    stdin = &keypadInput;
}

int keypadGetChar(FILE* stream)
{
    char key = NO_KEY;
    while ((key = keypad.getKey()) == NO_KEY) {
        delay(50);
    }
    return key;
}
