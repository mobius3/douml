#ifndef _UMLEXPANSIONREGION_H
#define _UMLEXPANSIONREGION_H


#include "UmlBaseExpansionRegion.h"
#include <QByteArray>

class UmlExpansionRegion : public UmlBaseExpansionRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlExpansionRegion(void * id, const QByteArray & s) : UmlBaseExpansionRegion(id, s) {
    }

};

#endif
