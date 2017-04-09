#ifndef _UMLACTIVITYCONTROLNODE_H
#define _UMLACTIVITYCONTROLNODE_H


#include "UmlBaseActivityControlNode.h"


class UmlActivityControlNode : public UmlBaseActivityControlNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityControlNode(void * id, const QByteArray & s) : UmlBaseActivityControlNode(id, s) {
    }


public:
    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
