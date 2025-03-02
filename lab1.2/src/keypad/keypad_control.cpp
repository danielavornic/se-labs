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
    while (true) {
        char key = keypad.getKey();
        // if key is pressed
        if (key != NO_KEY) {
            return key;
        }
        delay(50);
    }
}
