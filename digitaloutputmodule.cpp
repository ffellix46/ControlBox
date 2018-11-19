#include "digitaloutputmodule.h"

DigitalOutputModule::DigitalOutputModule()
{
    digitalOutputSetUp();

}

void DigitalOutputModule::digitalOutputSetUp(){

    fd_digital_output=pcf8574Setup(DIGITAL_OUTPUT_BASE,ADDRESS_DIGITAL_OUTPUT);

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

}

UA_DataSource DigitalOutputModule::digitalOutputData(int port){
    //UA_DataSource digitalOutputData;

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

    }

    //return digitalOutputData;
}

UA_StatusCode DigitalOutputModule::readCurrentDigitalOutputZero(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue) {

    UA_Boolean statusDO0;
    if(digitalRead(DIGITAL_OUTPUT_BASE+0))
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


    if(digitalRead(DIGITAL_OUTPUT_BASE+0)){
        digitalWrite(DIGITAL_OUTPUT_BASE+0,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+0,1);
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

    UA_Boolean statusDO1;
    if(digitalRead(DIGITAL_OUTPUT_BASE+1))
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


    if(digitalRead(DIGITAL_OUTPUT_BASE+1)){
        digitalWrite(DIGITAL_OUTPUT_BASE+1,0);
    }else{
        digitalWrite(DIGITAL_OUTPUT_BASE+1,1);
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Digital Output  1 changed");


    return UA_STATUSCODE_GOOD;
}
