#ifndef UMLNODE_H
#define UMLNODE_H

#include "UmlBaseNode.h"
//Added by qt3to4:
#include "misc/mystr.h"

// This class manages 'nodes'
// You can modify it as you want (except the constructor)

class UmlNode : public UmlBaseNode
{
public:
    UmlNode(void * id, const WrapperStr & n)
        : UmlBaseNode(id, n) {};
};

#endif
