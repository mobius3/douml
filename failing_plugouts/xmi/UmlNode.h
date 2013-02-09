#ifndef _UMLNODE_H
#define _UMLNODE_H


#include "UmlBaseNode.h"
#include <q3cstring.h>

class FileOut;

// This class manages 'nodes'
//
// You can modify it as you want (except the constructor)
class UmlNode : public UmlBaseNode
{
public:
    UmlNode(void * id, const Q3CString & n) : UmlBaseNode(id, n) {};

    virtual bool write_if_needed(FileOut & out);

    virtual void write(FileOut & out);

};

#endif
