#include "analoginputmodule.h"

//int file_i2c;
//int length;
//unsigned char buffer[60] = {0};


AnalogInputModule::AnalogInputModule()
{
    analogInputSetUp();
//    int i;
//    float adc[8];
//    char buffer[17];
//    fd_analog_input= open("/dev/i2c-1",O_RDWR);

//    if(fd_analog_input<0){
//        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                    "Failed to open the i2c bus.");
//        return;
//    }

//    if (ioctl(fd_analog_input, I2C_SLAVE, ADDRESS_ANALOG_INPUT) < 0)
//    {
//        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                    "Failed to acquire bus access and/or talk to slave.");
//        close(fd_analog_input);
//        return;
//    }

//    char echar[]={0};

//    r=write(fd_analog_input,echar,1);
//    if(r<0){
//        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                    "Failed to write to the i2c bus.");
//        return;
//    }

//    r=read(fd_analog_input,buffer,sizeof(buffer));
//    close(fd_analog_input);
//    qDebug()<<+"r="+QString::number(r);

//    if(r<0){
//        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
//                    "Failed to read from the i2c bus.");
//        return;
//    }

//    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Reading analog...");
//    for(i=1;i<sizeof(buffer);i++)
//        qDebug()<<"Buffer: "+QString::number(buffer[i]);
//    for(i=0;i<8;i++){
//        adc[i]=buffer[(i*2)+2]*256+buffer[(i*2)+1];
//        qDebug()<<"ADC"+QString::number(i)+": "+QString::number(adc[i]);
//        qDebug()<<"Volt"+QString::number(i)+": "+QString::number(adc[i]*10/999.0234375);

//    }

}

bool AnalogInputModule::analogInputSetUp(){
        fd_analog_input= open("/dev/i2c-1",O_RDWR);

        if(fd_analog_input<0){
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Failed to open the AnalogInput i2c bus.");
            return 0;
        }

        if (ioctl(fd_analog_input, I2C_SLAVE, ADDRESS_ANALOG_INPUT) < 0)
        {
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Failed to acquire bus access and/or talk to AnalogInput slave.");
            close(fd_analog_input);
            return 0;
        }

        char echar[]={0};

        r=write(fd_analog_input,echar,1);
        if(r<0){
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Failed to write to the AnalogInput i2c bus.");
            return 0;
        }

        r=read(fd_analog_input,buffer,sizeof(buffer));

        qDebug()<<+"r="+QString::number(r);

        if(r<0){
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Failed to read from the AnalogInput i2c bus.");
            return 0;
        }
}

void AnalogInputModule::addAnalogInputVariable(UA_Server *server){
       UA_Float now = 0;
       UA_VariableAttributes attr = UA_VariableAttributes_default;
       attr.displayName = UA_LOCALIZEDTEXT("en-US", "Analog Input");
       attr.accessLevel = UA_ACCESSLEVELMASK_READ;
       UA_Variant_setScalar(&attr.value, &now, &UA_TYPES[UA_TYPES_FLOAT]);

       UA_NodeId currentNodeId = UA_NODEID_STRING(1, "analog-input");
       UA_QualifiedName currentName = UA_QUALIFIEDNAME(1, "analog-input");
       UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
       UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
       UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);
       UA_Server_addVariableNode(server, currentNodeId, parentNodeId,
                                 parentReferenceNodeId, currentName,
                                 variableTypeNodeId, attr, NULL, NULL);

       updateInput(server);
}

void AnalogInputModule::updateInput(UA_Server *server){
    AnalogInputModule aim;
    float result=aim.readAnalogInput(3);
    UA_Float now = result;
    UA_Variant value;
    UA_Variant_setScalar(&value, &now, &UA_TYPES[UA_TYPES_FLOAT]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "analog-input");
    UA_Server_writeValue(server, currentNodeId, value);
}

float AnalogInputModule::readAnalogInput(int port){

    int i;
    char echar[]={0};
    float adc[8];

    r=write(fd_analog_input,echar,1);
    if(r<0){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Failed to write to the AnalogInput i2c bus.");
        return 0;
    }

    r=read(fd_analog_input,buffer,sizeof(buffer));

    qDebug()<<+"r2="+QString::number(r);

    if(r<0){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Failed to read from the AnalogInput i2c bus.");
        return 0;
    }

    for(i=1;i<sizeof(buffer);i++)
         qDebug()<<"Buffer: "+QString::number(buffer[i]);
    for(i=0;i<8;i++){
         adc[i]=buffer[(i*2)+2]*256+buffer[(i*2)+1];
         qDebug()<<"ADC"+QString::number(i)+": "+QString::number(adc[i]);
         qDebug()<<"Volt"+QString::number(i)+": "+QString::number(adc[i]*10/999.0234375);

    }
    return adc[port];
}
