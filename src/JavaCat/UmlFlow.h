#ifndef _UMLFLOW_H
#define _UMLFLOW_H


#include "UmlBaseFlow.h"
#include "UmlActivityItem.h"
#include "misc/mystr.h"

class UmlFlow : public UmlBaseFlow, public UmlActivityItem
{
public:
    UmlFlow(void * id, const WrapperStr & n) : UmlBaseFlow(id, n) {
    }

};

#endif
