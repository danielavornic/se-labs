#include "serial_comm.h"

static FILE serialOutput = { 0 };

static int serialWriteByte(char c, FILE* stream)
{
    if (c == '\n') {
        Serial.write('\n');
        Serial.write('\r');
    } else {
        Serial.write(c);
    }

    return 0;
}

void initSerial()
{
    Serial.begin(SERIAL_BAUD_RATE);

    while (!Serial) {
        ;
    }

    fdev_setup_stream(&serialOutput, serialWriteByte, NULL, _FDEV_SETUP_WRITE);
    stdout = &serialOutput;
}