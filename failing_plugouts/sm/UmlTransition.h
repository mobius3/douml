#ifndef _UMLTRANSITION_H
#define _UMLTRANSITION_H


#include "UmlBaseTransition.h"
#include "UmlStateItem.h"
#include <q3cstring.h>
#include <q3ptrlist.h>

class UmlClass;
class UmlState;

class UmlTransition : public UmlBaseTransition, public UmlStateItem
{
public:
    UmlTransition(void * id, const Q3CString & n) : UmlBaseTransition(id, n), _already_managed(FALSE) {
    }

    //  return the name of the trigger

    Q3CString triggerName();

    //  initialization before generation

    virtual void init(UmlClass * mother, Q3CString path, Q3CString pretty_path, UmlState * state);

    //   manage transition from a state or an initial pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state);

    //  manage transition from a pseudo state

    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent);

    //  generate all the transition in trs, for a state, junction or choice

    static void generate(Q3PtrList<UmlTransition> trs, UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent, bool completion);


protected:
    //  to know that the transition was already managed because
    //  it has the same trigger of an other transition
    bool _already_managed;

};

#endif
