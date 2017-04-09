#ifndef _UMLCLASSINSTANCE_H
#define _UMLCLASSINSTANCE_H


#include "UmlBaseClassInstance.h"


class UmlClassInstance : public UmlBaseClassInstance
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlClassInstance(void * id, const QByteArray & s) : UmlBaseClassInstance(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
