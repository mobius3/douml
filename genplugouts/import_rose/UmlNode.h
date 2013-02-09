#ifndef _UMLNODE_H
#define _UMLNODE_H


#include "UmlBaseNode.h"
#include <q3cstring.h>

class File;
class UmlDeploymentView;

// This class manages 'nodes'
//
// You can modify it as you want (except the constructor)
class UmlNode : public UmlBaseNode
{
public:
    UmlNode(void * id, const Q3CString & n) : UmlBaseNode(id, n) {
        cpt[kind()] += 1;
    };

    static void import(File & f, UmlDeploymentView * p, const Q3CString & ste);

};

#endif
