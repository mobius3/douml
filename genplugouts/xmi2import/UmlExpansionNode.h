#ifndef _UMLEXPANSIONNODE_H
#define _UMLEXPANSIONNODE_H


#include "UmlBaseExpansionNode.h"
#include <q3cstring.h>

class FileIn;
class Token;
class UmlItem;

class UmlExpansionNode : public UmlBaseExpansionNode {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlExpansionNode(void * id, const Q3CString & s) : UmlBaseExpansionNode(id, s) {
    }

    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

#endif
