/*
 * DigitalOutputModule handles the communication via I2C between the Digital Output Module and the OPC Server
 *
 * @author  Fernando Felix, Kevin Martin, Sathwik Rongala
 * @version 1.2, 19/11/18
 * @see      controlboxserver.cpp
 */



#include "digitaloutputmodule.h"

DigitalOutputModule::DigitalOutputModule()
{
    digitalOutputSetUp();

}

void DigitalOutputModule::digitalOutputSetUp(){

    fd_digital_output=pcf8574Setup(DIGITAL_OUTPUT_BASE,ADDRESS_DIGITAL_OUTPUT);

    if(fd_digital_output<0){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Failed to open the DigitalOutput i2c bus.");
        return;
    }

    for(int i=0;i<8;i++){
        pinMode(DIGITAL_OUTPUT_BASE+i,OUTPUT);
        digitalWrite(DIGITAL_OUTPUT_BASE+i,1);
    }

}

void DigitalOutputModule::addDigitalOutputVariable(UA_Server *server) {
        UA_NodeId digitalOutputId; /* get the nodeid assigned by the server */
        UA_NodeId currentNodeId = UA_NODEID_NULL;
        UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
        UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);


        UA_ObjectAttributes digitalOutputAttr = UA_ObjectAttributes_default;
        digitalOutputAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Output Node");
        UA_Server_addObjectNode(server, currentNodeId,
                                UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                                UA_QUALIFIEDNAME(1, "Digital Output Node"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                                digitalOutputAttr, NULL, &digitalOutputId);

        UA_VariableAttributes statuDO0Attr = UA_VariableAttributes_default;
        UA_Boolean statusDO0 = false;
        UA_Variant_setScalar(&statuDO0Attr.value, &statusDO0, &UA_TYPES[UA_TYPES_BOOLEAN]);
        statuDO0Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DO0");
        statuDO0Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        UA_Server_addDataSourceVariableNode(server, currentNodeId, digitalOutputId,
                                            parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DO0"),
                                            variableTypeNodeId, statuDO0Attr,
                                            digitalOutputData(DO0), NULL, NULL);

        UA_VariableAttributes statuDO1Attr = UA_VariableAttributes_default;
        UA_Boolean statusDO1 = false;
        UA_Variant_setScalar(&statuDO1Attr.value, &statusDO1, &UA_TYPES[UA_TYPES_BOOLEAN]);
        statuDO1Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DO1");
        statuDO1Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        UA_Server_addDataSourceVariableNode(server, currentNodeId, digitalOutputId,
                                            parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DO1"),
                                            variableTypeNodeId, statuDO1Attr,
                                            digitalOutputData(DO1), NULL, NULL);


        UA_VariableAttributes statuDO2Attr = UA_VariableAttributes_default;
        UA_Boolean statusDO2 = false;
        UA_Variant_setScalar(&statuDO2Attr.value, &statusDO2, &UA_TYPES[UA_TYPES_BOOLEAN]);
        statuDO2Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DO2");
        statuDO2Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        UA_Server_addDataSourceVariableNode(server, currentNodeId, digitalOutputId,
                                            parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DO2"),
                                            variableTypeNodeId, statuDO2Attr,
                                            digitalOutputData(DO2), NULL, NULL);


        UA_VariableAttributes statuDO3Attr = UA_VariableAttributes_default;
        UA_Boolean statusDO3 = false;
        UA_Variant_setScalar(&statuDO3Attr.value, &statusDO3, &UA_TYPES[UA_TYPES_BOOLEAN]);
        statuDO3Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DO3");
        statuDO3Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        UA_Server_addDataSourceVariableNode(server, currentNodeId, digitalOutputId,
                                            parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DO3"),
                                            variableTypeNodeId, statuDO3Attr,
                                            digitalOutputData(DO3), NULL, NULL);


        UA_VariableAttributes statuDO4Attr = UA_VariableAttributes_default;
        UA_Boolean statusDO4 = false;
        UA_Variant_setScalar(&statuDO4Attr.value, &statusDO4, &UA_TYPES[UA_TYPES_BOOLEAN]);
        statuDO4Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DO4");
        statuDO4Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
        UA_Server_addDataSourceVariableNode(server, currentNodeId, digitalOutputId,
                                            parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DO4"),
                                            variableTypeNodeId, statuDO4Attr,
                                            digitalOutputData(DO4), NULL, NULL);

}

UA_DataSource DigitalOutputModule::digitalOutputData(int port){

    switch(port){
    case DO0:
        UA_DataSource digitalOutputDataZero;
        digitalOutputDataZero.read = readCurrentDigitalOutputZero;
        digitalOutputDataZero.write = writeCurrentDigitalOutputZero;
        return digitalOutputDataZero;
    case DO1:
        UA_DataSource digitalOutputDataOne;
        digitalOutputDataOne.read = readCurrentDigitalOutputOne;
        digitalOutputDataOne.write = writeCurrentDigitalOutputOne;
        return digitalOutputDataOne;
    case DO2:
        UA_DataSource digitalOutputDataTwo;
        digitalOutputDataTwo.read = readCurrentDigitalOutputTwo;
        digitalOutputDataTwo.write = writeCurrentDigitalOutputTwo;
        return digitalOutputDataTwo;
    case DO3:
        UA_DataSource digitalOutputDataThree;
        digitalOutputDataThree.read = readCurrentDigitalOutputThree;
        digitalOutputDataThree.write = writeCurrentDigitalOutputThree;
        return digitalOutputDataThree;
    case DO4:
        UA_DataSource digitalOutputDataFour;
        digitalOutputDataFour.read = readCurrentDigitalOutputFour;
        digitalOutputDataFour.write = writeCurrentDigitalOutputFour;
        return digitalOutputDataFour;

    }

}



UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputZero(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    qDebug()<<&dataValue->value;

    UA_Boolean statusDO0;
    if(digitalRead(DIGITAL_OUTPUT_BASE+DO0))
        statusDO0=false;
    else
        statusDO0=true;

    UA_Variant_setScalarCopy(&dataValue->value, &statusDO0, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


UA_StatusCode DigitalOutputModule::writeCurrentDigitalOutputZero(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {


    if(digitalRead(DIGITAL_OUTPUT_BASE+DO0)){
        digitalWrite(DIGITAL_OUTPUT_BASE+DO0,0); //ON
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+DO0,1); //OFF
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  0 changed");


    return UA_STATUSCODE_GOOD;
}

UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputOne(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    qDebug()<<&dataValue->value;

    UA_Boolean statusDO1;
    if(digitalRead(DIGITAL_OUTPUT_BASE+DO1))
        statusDO1=false;
    else
        statusDO1=true;

    UA_Variant_setScalarCopy(&dataValue->value, &statusDO1, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


UA_StatusCode DigitalOutputModule::writeCurrentDigitalOutputOne(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {


    if(digitalRead(DIGITAL_OUTPUT_BASE+DO1)){
        digitalWrite(DIGITAL_OUTPUT_BASE+DO1,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+DO1,1);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  1 changed");


    return UA_STATUSCODE_GOOD;
}

UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputTwo(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    UA_Boolean statusDO2;
    if(digitalRead(DIGITAL_OUTPUT_BASE+2))
        statusDO2=false;
    else
        statusDO2=true;

    UA_Variant_setScalarCopy(&dataValue->value, &statusDO2, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


UA_StatusCode DigitalOutputModule::writeCurrentDigitalOutputTwo(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {


    if(digitalRead(DIGITAL_OUTPUT_BASE+2)){
        digitalWrite(DIGITAL_OUTPUT_BASE+2,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+2,1);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  2 changed");


    return UA_STATUSCODE_GOOD;
}

UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputThree(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    UA_Boolean statusDO3;
    if(digitalRead(DIGITAL_OUTPUT_BASE+3))
        statusDO3=false;
    else
        statusDO3=true;

    UA_Variant_setScalarCopy(&dataValue->value, &statusDO3, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


UA_StatusCode DigitalOutputModule::writeCurrentDigitalOutputThree(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {


    if(digitalRead(DIGITAL_OUTPUT_BASE+3)){
        digitalWrite(DIGITAL_OUTPUT_BASE+3,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+3,1);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  3 changed");


    return UA_STATUSCODE_GOOD;
}
UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputFour(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    UA_Boolean statusDO4;
    if(digitalRead(DIGITAL_OUTPUT_BASE+4))
        statusDO4=false;
    else
        statusDO4=true;

    UA_Variant_setScalarCopy(&dataValue->value, &statusDO4, &UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}


UA_StatusCode DigitalOutputModule::writeCurrentDigitalOutputFour(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data) {


    if(digitalRead(DIGITAL_OUTPUT_BASE+4)){
        digitalWrite(DIGITAL_OUTPUT_BASE+4,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+4,1);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  4 changed");


    return UA_STATUSCODE_GOOD;
}
