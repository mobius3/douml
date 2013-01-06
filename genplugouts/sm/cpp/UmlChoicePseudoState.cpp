
#include "UmlChoicePseudoState.h"
#include "UmlClass.h"
#include "UmlState.h"

#include "UmlTransition.h"
//Added by qt3to4:
#include <Q3CString>

void UmlChoicePseudoState::generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent)
{
    const Q3PtrVector<UmlItem> ch = children();
    Q3PtrList<UmlTransition> trs;
    unsigned index;

    for (index = 0; index != ch.count(); index += 1)
        if (ch[index]->kind() == aTransition)
            // theo mandatory
            trs.append((UmlTransition *) ch[index]);

    UmlTransition::generate(trs, machine, anystate, state, body, indent, FALSE);
}

