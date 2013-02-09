#ifndef _UMLNODE_H
#define _UMLNODE_H


#include "UmlBaseNode.h"


class FileOut;

// This class manages 'nodes'
//
// You can modify it as you want (except the constructor)
class UmlNode : public UmlBaseNode
{
public:
    UmlNode(void * id, const WrapperStr & n) : UmlBaseNode(id, n) {};

    virtual void write(FileOut & out);

};

#endif
