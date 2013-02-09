
#include "UmlFinalState.h"
#include "UmlClass.h"
#include "UmlState.h"

#include "UmlCom.h"
#include "UmlOperation.h"
#include "UmlTransition.h"
//Added by qt3to4:
#include <Q3CString>

void UmlFinalState::generate(UmlClass *, UmlClass *, UmlState *, Q3CString & body, Q3CString indent)
{
    if (parent()->kind() != aRegion)
        body += indent + "stm._final();\n";
    else {
#ifndef WIN32
#warning A FAIRE
#endif
    }
}

