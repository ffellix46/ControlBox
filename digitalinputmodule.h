#ifndef DIGITALINPUTMODULE_H
#define DIGITALINPUTMODULE_H


#include "open62541.h"
#include "/usr/include/wiringPi.h"
#include "/usr/include/wiringPiI2C.h"
#include "/usr/include/pcf8574.h"
#include "/usr/include/time.h"

#define ADDRESS_DIGITAL_INPUT 0x999
#define DIGITAL_INPUT_BASE 100
#define DI0 0
#define DI1 1
#define DI2 2
#define DI3 3
#define DI4 4
#define DI5 5


class DigitalInputModule
{
public:
    DigitalInputModule();
    static void addDigitalInputVariable(UA_Server *server);

private:
    int fd_digital_output = 0;
    void digitalInputSetUp();
    static void updateInput(UA_Server *server);
};

#endif // DIGITALINPUTMODULE_H
