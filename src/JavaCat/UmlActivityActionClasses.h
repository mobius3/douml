#ifndef _UMLACTIVITYACTIONCLASSES_H
#define _UMLACTIVITYACTIONCLASSES_H


#include "UmlBaseActivityActionClasses.h"
#include "misc/mystr.h"

class UmlSendObjectAction : public UmlBaseSendObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendObjectAction(void * id, const WrapperStr & s) : UmlBaseSendObjectAction(id, s) {
    }

};

class UmlUnmarshallAction : public UmlBaseUnmarshallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlUnmarshallAction(void * id, const WrapperStr & s) : UmlBaseUnmarshallAction(id, s) {
    }

};

class UmlSendSignalAction : public UmlBaseSendSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendSignalAction(void * id, const WrapperStr & s) : UmlBaseSendSignalAction(id, s) {
    }

};

class UmlBroadcastSignalAction : public UmlBaseBroadcastSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBroadcastSignalAction(void * id, const WrapperStr & s) : UmlBaseBroadcastSignalAction(id, s) {
    }

};

class UmlValueSpecificationAction : public UmlBaseValueSpecificationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlValueSpecificationAction(void * id, const WrapperStr & s) : UmlBaseValueSpecificationAction(id, s) {
    }

};

class UmlOpaqueAction : public UmlBaseOpaqueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOpaqueAction(void * id, const WrapperStr & s) : UmlBaseOpaqueAction(id, s) {
    }

};

class UmlAcceptEventAction : public UmlBaseAcceptEventAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptEventAction(void * id, const WrapperStr & s) : UmlBaseAcceptEventAction(id, s) {
    }

};

class UmlCallOperationAction : public UmlBaseCallOperationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallOperationAction(void * id, const WrapperStr & s) : UmlBaseCallOperationAction(id, s) {
    }

};

class UmlCallBehaviorAction : public UmlBaseCallBehaviorAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallBehaviorAction(void * id, const WrapperStr & s) : UmlBaseCallBehaviorAction(id, s) {
    }

};

class UmlClearVariableValueAction : public UmlBaseClearVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClearVariableValueAction(void * id, const WrapperStr & s) : UmlBaseClearVariableValueAction(id, s) {
    }

};

class UmlReadVariableValueAction : public UmlBaseReadVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReadVariableValueAction(void * id, const WrapperStr & s) : UmlBaseReadVariableValueAction(id, s) {
    }

};

class UmlWriteVariableValueAction : public UmlBaseWriteVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlWriteVariableValueAction(void * id, const WrapperStr & s) : UmlBaseWriteVariableValueAction(id, s) {
    }

};

class UmlAddVariableValueAction : public UmlBaseAddVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAddVariableValueAction(void * id, const WrapperStr & s) : UmlBaseAddVariableValueAction(id, s) {
    }

};

class UmlRemoveVariableValueAction : public UmlBaseRemoveVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRemoveVariableValueAction(void * id, const WrapperStr & s) : UmlBaseRemoveVariableValueAction(id, s) {
    }

};

class UmlAcceptCallAction : public UmlBaseAcceptCallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptCallAction(void * id, const WrapperStr & s) : UmlBaseAcceptCallAction(id, s) {
    }

};

class UmlReplyAction : public UmlBaseReplyAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReplyAction(void * id, const WrapperStr & s) : UmlBaseReplyAction(id, s) {
    }

};

class UmlCreateObjectAction : public UmlBaseCreateObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCreateObjectAction(void * id, const WrapperStr & s) : UmlBaseCreateObjectAction(id, s) {
    }

};

class UmlDestroyObjectAction : public UmlBaseDestroyObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDestroyObjectAction(void * id, const WrapperStr & s) : UmlBaseDestroyObjectAction(id, s) {
    }

};

class UmlTestIdentityAction : public UmlBaseTestIdentityAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlTestIdentityAction(void * id, const WrapperStr & s) : UmlBaseTestIdentityAction(id, s) {
    }

};

class UmlRaiseExceptionAction : public UmlBaseRaiseExceptionAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRaiseExceptionAction(void * id, const WrapperStr & s) : UmlBaseRaiseExceptionAction(id, s) {
    }

};

class UmlReduceAction : public UmlBaseReduceAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReduceAction(void * id, const WrapperStr & s) : UmlBaseReduceAction(id, s) {
    }

};

#endif
