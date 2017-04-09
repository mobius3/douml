
#include "UmlExitPointPseudoState.h"

#include "UmlCom.h"
#include "FileIn.h"
//Added by qt3to4:
#include "misc/mystr.h"
void UmlExitPointPseudoState::solve(WrapperStr idref)
{
    // note : parent state already resolved => is a state reference
    QMap<QString, UmlItem *>::Iterator it = All.find(idref);

    if (it == All.end()) {
        if (!FileIn::isBypassedId(idref))
            UmlCom::trace("state : unknown exit point reference '" + idref + "'<br>");
    }
    else if ((*it)->kind() == anExitPointPseudoState)
        set_Reference((UmlExitPointPseudoState *) *it);


}

