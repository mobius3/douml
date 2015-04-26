#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"


class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInterruptibleActivityRegion(void * id, const QByteArray & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
