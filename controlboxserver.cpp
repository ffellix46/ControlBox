#include "controlboxserver.h"

UA_Boolean running = true;

ControlBoxServer::ControlBoxServer()
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    config=UA_ServerConfig_new_default();
    server=UA_Server_new(config);

    wiringPiSetup();
}

//OPC Server

void ControlBoxServer::stopHandler(int sig) {
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

int ControlBoxServer::handleServer() {
    UA_StatusCode retval = UA_Server_run(server, &running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);

    return retval;
}

//Digital Output Module

void ControlBoxServer::addDigitalOutputModule(){
    DigitalOutputModule *digitalOutputModule = new DigitalOutputModule();
    digitalOutputModule->addDigitalOutputVariable(server);
}
