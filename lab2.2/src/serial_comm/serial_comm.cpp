#include "serial_comm.h"

static FILE serialOutput = { 0 };

static int serialWriteByte(char c, FILE* stream)
{
    if (c == 0) {
        Serial.write('\n'); // Print a newline
        Serial.write('\r'); // Add a carriage return for compatibility
    } else {
        Serial.write(c); // Write the character to Serial
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