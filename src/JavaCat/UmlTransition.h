#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include "misc/mystr.h"

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const WrapperStr & n) : UmlBaseTransition(id, n) {
    }

};

#endif
