#ifndef _UMLINTERRUPTIBLEACTIVITYREGION_H
#define _UMLINTERRUPTIBLEACTIVITYREGION_H


#include "UmlBaseInterruptibleActivityRegion.h"
#include "misc/mystr.h"

class UmlInterruptibleActivityRegion : public UmlBaseInterruptibleActivityRegion
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlInterruptibleActivityRegion(void * id, const WrapperStr & s) : UmlBaseInterruptibleActivityRegion(id, s) {
    }

};

#endif
