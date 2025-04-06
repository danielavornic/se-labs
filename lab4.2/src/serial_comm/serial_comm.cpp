#include "serial_comm.h"
#include "../config/config.h"

static FILE serialOutput = { 0 };
static FILE serialInput = { 0 };

static int serialWriteByte(char c, FILE* stream)
{
    if (c == '\n' || c == '\r') {
        Serial.write('\n');
        Serial.write('\r');
    } else {
        Serial.write(c);
    }
    return 0;
}

static int serialReadByte(FILE* stream)
{
    while (!Serial.available())
        ;
    return Serial.read();
}

void initSerial()
{
    Serial.begin(SERIAL_BAUD_RATE);

    while (!Serial) {
        ;
    }

    fdev_setup_stream(&serialOutput, serialWriteByte, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&serialInput, NULL, serialReadByte, _FDEV_SETUP_READ);

    stdout = &serialOutput;
    stdin = &serialInput;
}