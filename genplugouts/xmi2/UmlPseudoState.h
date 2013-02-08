#ifndef _UMLPSEUDOSTATE_H
#define _UMLPSEUDOSTATE_H


#include "UmlTransition.h"

#include "UmlItem.h"
#include "UmlStateItem.h"
#include <q3ptrlist.h>

class UmlTransition;
class FileOut;

class UmlPseudoState : public UmlStateItem, public UmlItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlPseudoState(void * id, const WrapperStr & s) : UmlItem(id, s) {
    }

    //goes among tree to memorize incoming transitions

    virtual void memo_incoming_trans();

    //memorize a new incoming transition
    void add_incoming_trans(UmlTransition * tr);

    virtual void write(FileOut & out);

    virtual const char * sKind() const = 0;


protected:
    Q3PtrList<UmlTransition> _incoming_trans;

};

#endif
