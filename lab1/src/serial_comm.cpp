#include "serial_comm.h"
#include "led_control.h"

// stream for stdio
static FILE serialOutput = { 0 };
static FILE serialInput = { 0 };

static int serialWriteByte(char c, FILE* stream)
{
    Serial.write(c);
    return 0;
}

static int serialReadByte(FILE* stream)
{
    while (!Serial.available())
        ;
    return Serial.read();
}

void serialInit()
{
    Serial.begin(SERIAL_BAUD_RATE);

    // wait for serial port to connect
    // for usb connection
    while (!Serial) {
        ;
    }

    fdev_setup_stream(&serialOutput, serialWriteByte, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&serialInput, NULL, serialReadByte, _FDEV_SETUP_READ);
    stdout = &serialOutput;
    stdin = &serialInput;

    printf("serial initialized. use 'led on' or 'led off' to control the LED\n");
}

void serialProcess()
{
    char command[MAX_MESSAGE_LENGTH];
    char modifier[MAX_MESSAGE_LENGTH];

    if (scanf("%s %s", command, modifier) == 2) {
        if (strcmp(command, "led") == 0) {
            if (strcmp(modifier, "on") == 0) {
                ledOn();
                printf("LED turned ON\n");
            } else if (strcmp(modifier, "off") == 0) {
                ledOff();
                printf("LED turned OFF\n");
            } else {
                printf("unknown modifier\n");
            }
        } else {
            printf("unknown command\n");
        }
    }
}