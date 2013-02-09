#ifndef _UMLACTIVITYCONTROLNODE_H
#define _UMLACTIVITYCONTROLNODE_H


#include "UmlBaseActivityControlNode.h"
#include "misc/mystr.h"

class UmlActivityControlNode : public UmlBaseActivityControlNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityControlNode(void * id, const WrapperStr & s) : UmlBaseActivityControlNode(id, s) {
    }

};

#endif
