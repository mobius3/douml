#ifndef _UMLEXPANSIONREGION_H
#define _UMLEXPANSIONREGION_H


#include "UmlBaseExpansionRegion.h"


class UmlExpansionRegion : public UmlBaseExpansionRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionRegion(void * id, const QByteArray & s) : UmlBaseExpansionRegion(id, s) {
    }

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

};

#endif
