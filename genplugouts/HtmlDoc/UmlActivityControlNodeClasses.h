#ifndef _UMLACTIVITYCONTROLNODECLASSES_H
#define _UMLACTIVITYCONTROLNODECLASSES_H


#include "UmlBaseActivityControlNodeClasses.h"


class UmlInitialActivityNode : public UmlBaseInitialActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInitialActivityNode(void * id, const QByteArray & s) : UmlBaseInitialActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlFlowFinalActivityNode : public UmlBaseFlowFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlFlowFinalActivityNode(void * id, const QByteArray & s) : UmlBaseFlowFinalActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlActivityFinalActivityNode : public UmlBaseActivityFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityFinalActivityNode(void * id, const QByteArray & s) : UmlBaseActivityFinalActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlDecisionActivityNode : public UmlBaseDecisionActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDecisionActivityNode(void * id, const QByteArray & s) : UmlBaseDecisionActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlMergeActivityNode : public UmlBaseMergeActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlMergeActivityNode(void * id, const QByteArray & s) : UmlBaseMergeActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlForkActivityNode : public UmlBaseForkActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlForkActivityNode(void * id, const QByteArray & s) : UmlBaseForkActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

class UmlJoinActivityNode : public UmlBaseJoinActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJoinActivityNode(void * id, const QByteArray & s) : UmlBaseJoinActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

};

#endif
