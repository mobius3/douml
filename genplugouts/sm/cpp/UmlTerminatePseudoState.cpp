
#include "UmlTerminatePseudoState.h"
#include "UmlClass.h"
#include "UmlState.h"
//Added by qt3to4:
#include <Q3CString>

void UmlTerminatePseudoState::generate(UmlClass *, UmlClass *, UmlState *, Q3CString & body, Q3CString indent)
{
    body += indent + "stm._final();\n";
}

