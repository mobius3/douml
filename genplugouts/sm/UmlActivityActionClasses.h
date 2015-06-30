#ifndef _UMLACTIVITYACTIONCLASSES_H
#define _UMLACTIVITYACTIONCLASSES_H


#include "UmlBaseActivityActionClasses.h"
#include <QByteArray>

class UmlSendObjectAction : public UmlBaseSendObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendObjectAction(void * id, const QByteArray & s) : UmlBaseSendObjectAction(id, s) {
    }

};

class UmlUnmarshallAction : public UmlBaseUnmarshallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlUnmarshallAction(void * id, const QByteArray & s) : UmlBaseUnmarshallAction(id, s) {
    }

};

class UmlSendSignalAction : public UmlBaseSendSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendSignalAction(void * id, const QByteArray & s) : UmlBaseSendSignalAction(id, s) {
    }

};

class UmlBroadcastSignalAction : public UmlBaseBroadcastSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBroadcastSignalAction(void * id, const QByteArray & s) : UmlBaseBroadcastSignalAction(id, s) {
    }

};

class UmlValueSpecificationAction : public UmlBaseValueSpecificationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlValueSpecificationAction(void * id, const QByteArray & s) : UmlBaseValueSpecificationAction(id, s) {
    }

};

class UmlOpaqueAction : public UmlBaseOpaqueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOpaqueAction(void * id, const QByteArray & s) : UmlBaseOpaqueAction(id, s) {
    }

};

class UmlAcceptEventAction : public UmlBaseAcceptEventAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptEventAction(void * id, const QByteArray & s) : UmlBaseAcceptEventAction(id, s) {
    }

};

class UmlCallOperationAction : public UmlBaseCallOperationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallOperationAction(void * id, const QByteArray & s) : UmlBaseCallOperationAction(id, s) {
    }

};

class UmlCallBehaviorAction : public UmlBaseCallBehaviorAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallBehaviorAction(void * id, const QByteArray & s) : UmlBaseCallBehaviorAction(id, s) {
    }

};

class UmlClearVariableValueAction : public UmlBaseClearVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClearVariableValueAction(void * id, const QByteArray & s) : UmlBaseClearVariableValueAction(id, s) {
    }

};

class UmlReadVariableValueAction : public UmlBaseReadVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReadVariableValueAction(void * id, const QByteArray & s) : UmlBaseReadVariableValueAction(id, s) {
    }

};

class UmlWriteVariableValueAction : public UmlBaseWriteVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlWriteVariableValueAction(void * id, const QByteArray & s) : UmlBaseWriteVariableValueAction(id, s) {
    }

};

class UmlAddVariableValueAction : public UmlBaseAddVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAddVariableValueAction(void * id, const QByteArray & s) : UmlBaseAddVariableValueAction(id, s) {
    }

};

class UmlRemoveVariableValueAction : public UmlBaseRemoveVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRemoveVariableValueAction(void * id, const QByteArray & s) : UmlBaseRemoveVariableValueAction(id, s) {
    }

};

#endif
