#include "serial_comm.h"
#include "led_control.h"

// stream for stdio
static FILE uartout = { 0 };
static FILE uartin = { 0 };

// uart - universal asynchronous receiver/transmitter
static int uart_putchar(char c, FILE* stream)
{
    Serial.write(c);
    return 0;
}

// input function
static int uart_getchar(FILE* stream)
{
    // wait until data is available
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
        ; // wait for serial port to connect
    }

    // Set up stdout and stdin
    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    fdev_setup_stream(&uartin, NULL, uart_getchar, _FDEV_SETUP_READ);
    stdout = &uartout;
    stdin = &uartin;

    printf("serial STDIO initialized\n");
}

bool serialIsDataAvailable()
{
    return Serial.available() > 0;
}

String serialReadMessage()
{
    return Serial.readStringUntil('\n');
}

void serialSendMessage(const char* message)
{
    Serial.println(message);
}

void serialProcess()
{
    char buffer[MAX_MESSAGE_LENGTH];

    if (Serial.available()) {
        if (fgets(buffer, MAX_MESSAGE_LENGTH, stdin) != NULL) {
            // Remove trailing newline or carriage return
            size_t len = strlen(buffer);
            while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
                buffer[len - 1] = '\0';
                len--;
            }

            if (strcmp(buffer, "led on") == 0) {
                ledOn();
                printf("LED turned ON\n");
            } else if (strcmp(buffer, "led off") == 0) {
                ledOff();
                printf("LED turned OFF\n");
            } else {
                printf("Unknown command. Use 'led on' or 'led off'\n");
            }
        }
    }
}