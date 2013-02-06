#ifndef _UMLEXPANSIONNODE_H
#define _UMLEXPANSIONNODE_H


#include "UmlBaseExpansionNode.h"
#include <q3cstring.h>

class UmlExpansionNode : public UmlBaseExpansionNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionNode(void * id, const Q3CString & s) : UmlBaseExpansionNode(id, s) {
    }

};

#endif
