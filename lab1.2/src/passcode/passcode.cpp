#include "passcode.h"
#include "keypad/keypad_control.h"
#include "lcd/lcd_control.h"
#include "led/led_control.h"
#include <string.h>

static char enteredCode[MAX_CODE_LENGTH + 1];
static int codeIndex = 0;

void passcodeInit()
{
    codeIndex = 0;
    memset(enteredCode, 0, sizeof(enteredCode));
    printf("\fEnter code:\n");
}

static void validatePasscode()
{
    if (strcmp(enteredCode, VALID_CODE) == 0) {
        printf("\fCode Valid!");
        ledGreenOn();
        ledRedOff();
    } else {
        printf("\fInvalid Code!");
        ledGreenOff();
        ledRedOn();
    }

    delay(2000);

    passcodeInit();
    ledGreenOff();
    ledRedOff();
}

void readPasscode()
{
    if (codeIndex < MAX_CODE_LENGTH) {
        char key;
        scanf("%c", &key);
        enteredCode[codeIndex] = key;
        printf("%c", key);
        codeIndex++;

        if (codeIndex == MAX_CODE_LENGTH) {
            // add null terminator to the end of the string
            enteredCode[codeIndex] = '\0';
            delay(500);
            validatePasscode();
        }
    }
}