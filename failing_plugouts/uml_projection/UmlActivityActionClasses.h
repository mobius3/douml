#ifndef _UMLACTIVITYACTIONCLASSES_H
#define _UMLACTIVITYACTIONCLASSES_H


#include "UmlBaseActivityActionClasses.h"
#include <q3cstring.h>

class UmlSendObjectAction : public UmlBaseSendObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendObjectAction(void * id, const Q3CString & s) : UmlBaseSendObjectAction(id, s) {
    }

};

class UmlUnmarshallAction : public UmlBaseUnmarshallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlUnmarshallAction(void * id, const Q3CString & s) : UmlBaseUnmarshallAction(id, s) {
    }

};

class UmlSendSignalAction : public UmlBaseSendSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendSignalAction(void * id, const Q3CString & s) : UmlBaseSendSignalAction(id, s) {
    }

};

class UmlBroadcastSignalAction : public UmlBaseBroadcastSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBroadcastSignalAction(void * id, const Q3CString & s) : UmlBaseBroadcastSignalAction(id, s) {
    }

};

class UmlValueSpecificationAction : public UmlBaseValueSpecificationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlValueSpecificationAction(void * id, const Q3CString & s) : UmlBaseValueSpecificationAction(id, s) {
    }

};

class UmlOpaqueAction : public UmlBaseOpaqueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOpaqueAction(void * id, const Q3CString & s) : UmlBaseOpaqueAction(id, s) {
    }

};

class UmlAcceptEventAction : public UmlBaseAcceptEventAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptEventAction(void * id, const Q3CString & s) : UmlBaseAcceptEventAction(id, s) {
    }

};

class UmlCallOperationAction : public UmlBaseCallOperationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallOperationAction(void * id, const Q3CString & s) : UmlBaseCallOperationAction(id, s) {
    }

};

class UmlCallBehaviorAction : public UmlBaseCallBehaviorAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallBehaviorAction(void * id, const Q3CString & s) : UmlBaseCallBehaviorAction(id, s) {
    }

};

class UmlClearVariableValueAction : public UmlBaseClearVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClearVariableValueAction(void * id, const Q3CString & s) : UmlBaseClearVariableValueAction(id, s) {
    }

};

class UmlReadVariableValueAction : public UmlBaseReadVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReadVariableValueAction(void * id, const Q3CString & s) : UmlBaseReadVariableValueAction(id, s) {
    }

};

class UmlWriteVariableValueAction : public UmlBaseWriteVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlWriteVariableValueAction(void * id, const Q3CString & s) : UmlBaseWriteVariableValueAction(id, s) {
    }

};

class UmlAddVariableValueAction : public UmlBaseAddVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAddVariableValueAction(void * id, const Q3CString & s) : UmlBaseAddVariableValueAction(id, s) {
    }

};

class UmlRemoveVariableValueAction : public UmlBaseRemoveVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRemoveVariableValueAction(void * id, const Q3CString & s) : UmlBaseRemoveVariableValueAction(id, s) {
    }

};

#endif
