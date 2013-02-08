#ifndef _UMLEXPANSIONNODE_H
#define _UMLEXPANSIONNODE_H


#include "UmlBaseExpansionNode.h"
#include "misc/mystr.h"

class UmlExpansionNode : public UmlBaseExpansionNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionNode(void * id, const WrapperStr & s) : UmlBaseExpansionNode(id, s) {
    }

};

#endif
