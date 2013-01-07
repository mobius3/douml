#ifndef _UMLSTATEDIAGRAM_H
#define _UMLSTATEDIAGRAM_H


#include <q3cstring.h>
#include "Vector.h"
#include "UmlBaseStateDiagram.h"
#include "UmlStateItem.h"

class UmlStateDiagram : public UmlBaseStateDiagram, public UmlStateItem
{
public:
    //set he html ref
    //set the diagrams list
    virtual void memo_ref();

    //returns a string indicating the king of the element
    virtual Q3CString sKind();

    static void ref_index();

    static void generate_index();


protected:
    static Vector diagrams;


public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlStateDiagram(void * id, const Q3CString & s) : UmlBaseStateDiagram(id, s) {
    }

};

#endif
