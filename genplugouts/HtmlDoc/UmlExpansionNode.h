#ifndef _UMLEXPANSIONNODE_H
#define _UMLEXPANSIONNODE_H


#include "UmlBaseExpansionNode.h"


class UmlExpansionNode : public UmlBaseExpansionNode
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionNode(void * id, const QByteArray & s) : UmlBaseExpansionNode(id, s) {
    }

};

#endif
