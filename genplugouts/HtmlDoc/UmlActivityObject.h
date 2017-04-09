#ifndef _UMLACTIVITYOBJECT_H
#define _UMLACTIVITYOBJECT_H


#include "UmlBaseActivityObject.h"


class UmlActivityObject : public UmlBaseActivityObject
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityObject(void * id, const QByteArray & s) : UmlBaseActivityObject(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html_internal(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
