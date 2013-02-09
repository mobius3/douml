#ifndef _UMLPSEUDOSTATE_H
#define _UMLPSEUDOSTATE_H


#include "misc/mystr.h"
#include "UmlItem.h"
#include "UmlStateItem.h"

class UmlPseudoState : public UmlStateItem, public UmlItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlPseudoState(void * id, const WrapperStr & s) : UmlItem(id, s) {
    }

};

#endif
