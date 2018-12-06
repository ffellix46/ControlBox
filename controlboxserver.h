#ifndef CONTROLBOXSERVER_H
#define CONTROLBOXSERVER_H

#include "open62541.h"
#include "digitaloutputmodule.h"
#include "digitalinputmodule.h"
#include "analoginputmodule.h"
#include "/usr/include/signal.h"

#define ADDRESS_ANALOG_INPUT 0x18
#define BASE 120


class ControlBoxServer{

public:
    ControlBoxServer();
    void addDigitalOutputModule();
    void addDigitalInputModule();
    void addAnalogInputModule();
    int handleServer();

private:
    UA_Server *server;
    UA_ServerConfig *config;

    static void stopHandler(int sig);

};

#endif // CONTROLBOXSERVER_H
