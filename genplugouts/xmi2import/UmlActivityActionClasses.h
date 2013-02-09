#ifndef _UMLACTIVITYACTIONCLASSES_H
#define _UMLACTIVITYACTIONCLASSES_H


#include "UmlBaseActivityActionClasses.h"


class FileIn;
class Token;
class UmlItem;

class UmlSendObjectAction : public UmlBaseSendObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendObjectAction(void * id, const WrapperStr & s) : UmlBaseSendObjectAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlUnmarshallAction : public UmlBaseUnmarshallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlUnmarshallAction(void * id, const WrapperStr & s) : UmlBaseUnmarshallAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlSendSignalAction : public UmlBaseSendSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendSignalAction(void * id, const WrapperStr & s) : UmlBaseSendSignalAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlBroadcastSignalAction : public UmlBaseBroadcastSignalAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBroadcastSignalAction(void * id, const WrapperStr & s) : UmlBaseBroadcastSignalAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlValueSpecificationAction : public UmlBaseValueSpecificationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlValueSpecificationAction(void * id, const WrapperStr & s) : UmlBaseValueSpecificationAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);


protected:
    void setValue(WrapperStr idref);


public:
    //  call at end of import : try to solve type or state
    virtual void solve(WrapperStr idref);

};

class UmlOpaqueAction : public UmlBaseOpaqueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOpaqueAction(void * id, const WrapperStr & s) : UmlBaseOpaqueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlAcceptEventAction : public UmlBaseAcceptEventAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptEventAction(void * id, const WrapperStr & s) : UmlBaseAcceptEventAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve trigger

    virtual void solve(WrapperStr idref);

};

class UmlCallOperationAction : public UmlBaseCallOperationAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallOperationAction(void * id, const WrapperStr & s) : UmlBaseCallOperationAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);


protected:
    void setOperation(WrapperStr idref);


public:
    //  call at end of import : try to solve oper
    virtual void solve(WrapperStr idref);

};

class UmlCallBehaviorAction : public UmlBaseCallBehaviorAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallBehaviorAction(void * id, const WrapperStr & s) : UmlBaseCallBehaviorAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);


protected:
    void setBehavior(WrapperStr idref);


public:
    //  call at end of import : try to solve behavior
    virtual void solve(WrapperStr idref);

};

class UmlClearVariableValueAction : public UmlBaseClearVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClearVariableValueAction(void * id, const WrapperStr & s) : UmlBaseClearVariableValueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlReadVariableValueAction : public UmlBaseReadVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReadVariableValueAction(void * id, const WrapperStr & s) : UmlBaseReadVariableValueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlWriteVariableValueAction : public UmlBaseWriteVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlWriteVariableValueAction(void * id, const WrapperStr & s) : UmlBaseWriteVariableValueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlAddVariableValueAction : public UmlBaseAddVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAddVariableValueAction(void * id, const WrapperStr & s) : UmlBaseAddVariableValueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlRemoveVariableValueAction : public UmlBaseRemoveVariableValueAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRemoveVariableValueAction(void * id, const WrapperStr & s) : UmlBaseRemoveVariableValueAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlAcceptCallAction : public UmlBaseAcceptCallAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptCallAction(void * id, const WrapperStr & s) : UmlBaseAcceptCallAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve trigger

    virtual void solve(WrapperStr idref);

};

class UmlReplyAction : public UmlBaseReplyAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReplyAction(void * id, const WrapperStr & s) : UmlBaseReplyAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve trigger

    virtual void solve(WrapperStr idref);

};

class UmlCreateObjectAction : public UmlBaseCreateObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCreateObjectAction(void * id, const WrapperStr & s) : UmlBaseCreateObjectAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve trigger

    virtual void solve(WrapperStr idref);

};

class UmlDestroyObjectAction : public UmlBaseDestroyObjectAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDestroyObjectAction(void * id, const WrapperStr & s) : UmlBaseDestroyObjectAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlTestIdentityAction : public UmlBaseTestIdentityAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlTestIdentityAction(void * id, const WrapperStr & s) : UmlBaseTestIdentityAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlRaiseExceptionAction : public UmlBaseRaiseExceptionAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRaiseExceptionAction(void * id, const WrapperStr & s) : UmlBaseRaiseExceptionAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

class UmlReduceAction : public UmlBaseReduceAction
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReduceAction(void * id, const WrapperStr & s) : UmlBaseReduceAction(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //  call at end of import : try to solve trigger

    virtual void solve(WrapperStr idref);

};

#endif
