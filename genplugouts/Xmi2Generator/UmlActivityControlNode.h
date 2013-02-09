#ifndef _UMLACTIVITYCONTROLNODE_H
#define _UMLACTIVITYCONTROLNODE_H


#include "UmlBaseActivityControlNode.h"


class FileOut;

class UmlActivityControlNode : public UmlBaseActivityControlNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityControlNode(void * id, const WrapperStr & s) : UmlBaseActivityControlNode(id, s) {
    }


public:
    //write the definition if it is not empty for the target language
    virtual void write(FileOut & out);

    virtual const char * sKind() const = 0;

};

#endif
