#include "serial_comm.h"

static FILE serialOutput = { 0 };

static int serialWriteByte(char c, FILE* stream)
{
    Serial.write(c);
    // add a carriage return after the newline
    if (c == '\n') {
        Serial.write('\r');
    }
    return 0;
}

void serialInit()
{
    Serial.begin(SERIAL_BAUD_RATE);

    while (!Serial) {
        ;
    }

    fdev_setup_stream(&serialOutput, serialWriteByte, NULL, _FDEV_SETUP_WRITE);
    stdout = &serialOutput;
}