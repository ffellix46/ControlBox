#include "digitalinputmodule.h"

DigitalInputModule::DigitalInputModule()
{

}

void DigitalInputModule::digitalInputSetUp(){

    fd_digital_output=pcf8574Setup(DIGITAL_INPUT_BASE,ADDRESS_DIGITAL_INPUT);

    for(int i=0;i<8;i++){
        pinMode(DIGITAL_INPUT_BASE+i,INPUT);
    }

}


void DigitalInputModule::addDigitalInputVariable(UA_Server *server) {
    UA_NodeId digitalInputId; /* get the nodeid assigned by the server */
    UA_NodeId currentNodeId = UA_NODEID_NULL;
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);


    UA_ObjectAttributes digitalInputAttr = UA_ObjectAttributes_default;
    digitalInputAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Digital Input Node");
    UA_Server_addObjectNode(server, currentNodeId,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Digital Input Node"), UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            digitalInputAttr, NULL, &digitalInputId);

    UA_VariableAttributes statuDI0Attr = UA_VariableAttributes_default;
    UA_Boolean statusDI0 = false;
    UA_Variant_setScalar(&statuDI0Attr.value, &statusDI0, &UA_TYPES[UA_TYPES_BOOLEAN]);
    statuDI0Attr.displayName = UA_LOCALIZEDTEXT("en-US", "Status DI0");
    statuDI0Attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(server, currentNodeId, digitalInputId,
                                        parentReferenceNodeId, UA_QUALIFIEDNAME(1, "Status DI0"),
                                        variableTypeNodeId, statuDI0Attr, NULL, NULL);

    updateInput(server);
}

void DigitalInputModule::updateInput(UA_Server *server) {
    UA_Boolean statusDI0 = true;
    UA_Variant value;
    UA_Variant_setScalar(&value, &statusDI0, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_NodeId currentNodeId = UA_NODEID_STRING(1, "Status DI0");
    UA_Server_writeValue(server, currentNodeId, value);
}
