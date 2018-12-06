#ifndef ANALOGINPUTMODULE_H
#define ANALOGINPUTMODULE_H

#include "open62541.h"
#include "/usr/include/linux/i2c-dev.h"
#include "/usr/include/unistd.h"
#include "/usr/include/fcntl.h"
#include "/usr/include/arm-linux-gnueabihf/sys/ioctl.h"
#include "/usr/include/time.h"
#include <QDebug>

#define ADDRESS_ANALOG_INPUT 0x18
#define ANALOG_INPUT_BASE 51


class AnalogInputModule
{
public:
    AnalogInputModule();
    static void addAnalogInputVariable(UA_Server *server);
    float readAnalogInput(int port);

private:
    int fd_analog_input = -1;
    int r;
    char buffer[17];
    bool analogInputSetUp();
    static void updateInput(UA_Server *server);
    //float readAnalogInput(int port);
};

#endif // ANALOGINPUTMODULE_H
