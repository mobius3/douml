#ifndef _UMLACTIVITYCONTROLNODE_H
#define _UMLACTIVITYCONTROLNODE_H


#include "UmlBaseActivityControlNode.h"


class FileIn;
class Token;
class UmlItem;

class UmlActivityControlNode : public UmlBaseActivityControlNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityControlNode(void * id, const WrapperStr & s) : UmlBaseActivityControlNode(id, s) {
    }


public:
    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

};

#endif
