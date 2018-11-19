#include <QCoreApplication>
#include "controlboxserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ControlBoxServer *controlBoxServer = new ControlBoxServer();

    controlBoxServer->addDigitalOutputModule();

    controlBoxServer->handleServer();

    return a.exec();
}
