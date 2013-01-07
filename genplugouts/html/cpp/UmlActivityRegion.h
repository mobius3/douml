#ifndef _UMLACTIVITYREGION_H
#define _UMLACTIVITYREGION_H


#include "UmlBaseActivityRegion.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>

class UmlActivityRegion : public UmlBaseActivityRegion, public UmlActivityItem
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityRegion(void * id, const Q3CString & s) : UmlBaseActivityRegion(id, s) {
    }


public:
    virtual bool chapterp();

};

#endif
