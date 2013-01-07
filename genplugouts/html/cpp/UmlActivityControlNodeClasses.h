#ifndef _UMLACTIVITYCONTROLNODECLASSES_H
#define _UMLACTIVITYCONTROLNODECLASSES_H


#include "UmlBaseActivityControlNodeClasses.h"
#include <q3cstring.h>

class UmlInitialActivityNode : public UmlBaseInitialActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInitialActivityNode(void * id, const Q3CString & s) : UmlBaseInitialActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlFlowFinalActivityNode : public UmlBaseFlowFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlFlowFinalActivityNode(void * id, const Q3CString & s) : UmlBaseFlowFinalActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlActivityFinalActivityNode : public UmlBaseActivityFinalActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityFinalActivityNode(void * id, const Q3CString & s) : UmlBaseActivityFinalActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlDecisionActivityNode : public UmlBaseDecisionActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlDecisionActivityNode(void * id, const Q3CString & s) : UmlBaseDecisionActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlMergeActivityNode : public UmlBaseMergeActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlMergeActivityNode(void * id, const Q3CString & s) : UmlBaseMergeActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlForkActivityNode : public UmlBaseForkActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlForkActivityNode(void * id, const Q3CString & s) : UmlBaseForkActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

class UmlJoinActivityNode : public UmlBaseJoinActivityNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlJoinActivityNode(void * id, const Q3CString & s) : UmlBaseJoinActivityNode(id, s) {
    }

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

};

#endif
