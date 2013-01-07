#ifndef _UMLACTIVITYPARTITION_H
#define _UMLACTIVITYPARTITION_H


#include "UmlBaseActivityPartition.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>

class UmlActivityPartition : public UmlBaseActivityPartition, public UmlActivityItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityPartition(void * id, const Q3CString & s) : UmlBaseActivityPartition(id, s) {
    }

};

#endif
