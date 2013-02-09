#ifndef _UMLACTIVITYCONTROLNODECLASSES_H
#define _UMLACTIVITYCONTROLNODECLASSES_H


#include "UmlBaseActivityControlNodeClasses.h"
#include "misc/mystr.h"

class UmlInitialActivityNode : public UmlBaseInitialActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInitialActivityNode(void * id, const WrapperStr & s) : UmlBaseInitialActivityNode(id, s) {
    }

};

class UmlFlowFinalActivityNode : public UmlBaseFlowFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlFlowFinalActivityNode(void * id, const WrapperStr & s) : UmlBaseFlowFinalActivityNode(id, s) {
    }

};

class UmlActivityFinalActivityNode : public UmlBaseActivityFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityFinalActivityNode(void * id, const WrapperStr & s) : UmlBaseActivityFinalActivityNode(id, s) {
    }

};

class UmlDecisionActivityNode : public UmlBaseDecisionActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDecisionActivityNode(void * id, const WrapperStr & s) : UmlBaseDecisionActivityNode(id, s) {
    }

};

class UmlMergeActivityNode : public UmlBaseMergeActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlMergeActivityNode(void * id, const WrapperStr & s) : UmlBaseMergeActivityNode(id, s) {
    }

};

class UmlForkActivityNode : public UmlBaseForkActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlForkActivityNode(void * id, const WrapperStr & s) : UmlBaseForkActivityNode(id, s) {
    }

};

class UmlJoinActivityNode : public UmlBaseJoinActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJoinActivityNode(void * id, const WrapperStr & s) : UmlBaseJoinActivityNode(id, s) {
    }

};

#endif
