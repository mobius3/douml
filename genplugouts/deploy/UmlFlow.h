#ifndef _UMLFLOW_H
#define _UMLFLOW_H


#include "UmlBaseFlow.h"
#include "UmlActivityItem.h"
#include <q3cstring.h>

class UmlFlow : public UmlBaseFlow, public UmlActivityItem
{
public:
    UmlFlow(void * id, const Q3CString & n) : UmlBaseFlow(id, n) {
    }

};

#endif
