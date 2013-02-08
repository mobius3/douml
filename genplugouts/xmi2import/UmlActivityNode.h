#ifndef _UMLACTIVITYNODE_H
#define _UMLACTIVITYNODE_H


#include "UmlBaseActivityNode.h"
#include "UmlActivityItem.h"


class UmlActivityNode : public UmlBaseActivityNode, public UmlActivityItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityNode(void * id, const WrapperStr & s) : UmlBaseActivityNode(id, s) {
    }

};

#endif
