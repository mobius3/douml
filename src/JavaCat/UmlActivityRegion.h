#ifndef _UMLACTIVITYREGION_H
#define _UMLACTIVITYREGION_H


#include "UmlBaseActivityRegion.h"
#include "UmlActivityItem.h"
#include "misc/mystr.h"

class UmlActivityRegion : public UmlBaseActivityRegion, public UmlActivityItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityRegion(void * id, const WrapperStr & s) : UmlBaseActivityRegion(id, s) {
    }

};

#endif
