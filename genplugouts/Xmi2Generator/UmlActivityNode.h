#ifndef _UMLACTIVITYNODE_H
#define _UMLACTIVITYNODE_H


#include "UmlFlow.h"
#include "UmlBaseActivityNode.h"
#include "UmlActivityItem.h"

#include <q3ptrlist.h>

class UmlFlow;
class FileOut;

class UmlActivityNode : public UmlBaseActivityNode, public UmlActivityItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityNode(void * id, const WrapperStr & s) : UmlBaseActivityNode(id, s) {
    }


public:
    //goes among tree to memorize incoming flow

    virtual void memo_incoming_flow();

    //memorize a new incoming flow

    void add_incoming_flow(UmlFlow * flow);

    //

    void write_incoming_flows(FileOut & out);


protected:
    //the flows whose target is the object
    Q3PtrList<UmlFlow> _incoming_flows;


public:
    virtual void solve_output_flows() = 0;

};

#endif
