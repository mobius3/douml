#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include <q3cstring.h>

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const Q3CString & n) : UmlBaseTransition(id, n) {
    }

};

#endif
