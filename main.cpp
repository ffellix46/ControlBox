/*
 * Main Programm. Creation of OPC Server and adding of I2C Modules.
 *
 * @author  Fernando Felix, Kevin Martin, Sathwik Rongala
 * @version 1.2, 19/11/18
 * @see      controlboxserver.cpp
 */

#include <QCoreApplication>
#include "controlboxserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ControlBoxServer *controlBoxServer = new ControlBoxServer();

    controlBoxServer->addDigitalOutputModule();

    controlBoxServer->addDigitalInputModule();

    controlBoxServer->handleServer();

    return a.exec();
}
