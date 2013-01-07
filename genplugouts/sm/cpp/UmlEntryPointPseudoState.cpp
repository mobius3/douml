
#include "UmlEntryPointPseudoState.h"
#include "UmlClass.h"
#include "UmlState.h"

#include "UmlCom.h"
#include "UmlTransition.h"
//Added by qt3to4:
#include <Q3CString>
void UmlEntryPointPseudoState::generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent)
{
    // check transition number
    const Q3PtrVector<UmlItem> ch = children();

    switch (ch.count()) {
    case 0:
        return;

    case 1:
        break;

    default:
        UmlCom::trace("Error : entry point '" + name() + "' can't have several transitions<br>");
        throw 0;
    }

    // here there is 1 transition
    ((UmlTransition *) ch[0])->generate(machine, anystate, state, body, indent);
}

