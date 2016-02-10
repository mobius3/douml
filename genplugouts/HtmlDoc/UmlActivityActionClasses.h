#ifndef _UMLACTIVITYACTIONCLASSES_H
#define _UMLACTIVITYACTIONCLASSES_H



#include "UmlBaseActivityActionClasses.h"

class UmlSendObjectAction : public UmlBaseSendObjectAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseSendObjectAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendObjectAction(void * id, const QByteArray & s) : UmlBaseSendObjectAction(id, s) {
    }

};

class UmlUnmarshallAction : public UmlBaseUnmarshallAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseUnmarshallAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlUnmarshallAction(void * id, const QByteArray & s) : UmlBaseUnmarshallAction(id, s) {
    }

};

class UmlSendSignalAction : public UmlBaseSendSignalAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlSendSignalAction(void * id, const QByteArray & s) : UmlBaseSendSignalAction(id, s) {
    }

};

class UmlBroadcastSignalAction : public UmlBaseBroadcastSignalAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBroadcastSignalAction(void * id, const QByteArray & s) : UmlBaseBroadcastSignalAction(id, s) {
    }

};

class UmlValueSpecificationAction : public UmlBaseValueSpecificationAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseValueSpecificationAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlValueSpecificationAction(void * id, const QByteArray & s) : UmlBaseValueSpecificationAction(id, s) {
    }

};

class UmlOpaqueAction : public UmlBaseOpaqueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseOpaqueAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlOpaqueAction(void * id, const QByteArray & s) : UmlBaseOpaqueAction(id, s) {
    }

};

class UmlAcceptEventAction : public UmlBaseAcceptEventAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseAcceptEventAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptEventAction(void * id, const QByteArray & s) : UmlBaseAcceptEventAction(id, s) {
    }

};

class UmlCallOperationAction : public UmlBaseCallOperationAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseCallOperationAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallOperationAction(void * id, const QByteArray & s) : UmlBaseCallOperationAction(id, s) {
    }

};

class UmlCallBehaviorAction : public UmlBaseCallBehaviorAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseCallBehaviorAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCallBehaviorAction(void * id, const QByteArray & s) : UmlBaseCallBehaviorAction(id, s) {
    }

};

class UmlClearVariableValueAction : public UmlBaseClearVariableValueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseClearVariableValueAction::html;
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClearVariableValueAction(void * id, const QByteArray & s) : UmlBaseClearVariableValueAction(id, s) {
    }

};

class UmlReadVariableValueAction : public UmlBaseReadVariableValueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReadVariableValueAction(void * id, const QByteArray & s) : UmlBaseReadVariableValueAction(id, s) {
    }

};

class UmlWriteVariableValueAction : public UmlBaseWriteVariableValueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlWriteVariableValueAction(void * id, const QByteArray & s) : UmlBaseWriteVariableValueAction(id, s) {
    }

};

class UmlAddVariableValueAction : public UmlBaseAddVariableValueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAddVariableValueAction(void * id, const QByteArray & s) : UmlBaseAddVariableValueAction(id, s) {
    }

};

class UmlRemoveVariableValueAction : public UmlBaseRemoveVariableValueAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRemoveVariableValueAction(void * id, const QByteArray & s) : UmlBaseRemoveVariableValueAction(id, s) {
    }

};

class UmlAcceptCallAction : public UmlBaseAcceptCallAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseAcceptCallAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlAcceptCallAction(void * id, const QByteArray & s) : UmlBaseAcceptCallAction(id, s) {
    }

};

class UmlReplyAction : public UmlBaseReplyAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseReplyAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReplyAction(void * id, const QByteArray & s) : UmlBaseReplyAction(id, s) {
    }

};

class UmlCreateObjectAction : public UmlBaseCreateObjectAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseCreateObjectAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlCreateObjectAction(void * id, const QByteArray & s) : UmlBaseCreateObjectAction(id, s) {
    }

};

class UmlDestroyObjectAction : public UmlBaseDestroyObjectAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseDestroyObjectAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDestroyObjectAction(void * id, const QByteArray & s) : UmlBaseDestroyObjectAction(id, s) {
    }

};

class UmlTestIdentityAction : public UmlBaseTestIdentityAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseTestIdentityAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlTestIdentityAction(void * id, const QByteArray & s) : UmlBaseTestIdentityAction(id, s) {
    }

};

class UmlRaiseExceptionAction : public UmlBaseRaiseExceptionAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseRaiseExceptionAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlRaiseExceptionAction(void * id, const QByteArray & s) : UmlBaseRaiseExceptionAction(id, s) {
    }

};

class UmlReduceAction : public UmlBaseReduceAction
{
public:
    //returns a string indicating the king of the element
    virtual QByteArray sKind() override;

    using UmlBaseReduceAction::html;
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) override;

    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlReduceAction(void * id, const QByteArray & s) : UmlBaseReduceAction(id, s) {
    }

};

#endif
