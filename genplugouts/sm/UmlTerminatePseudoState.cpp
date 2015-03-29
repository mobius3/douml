
#include "UmlTerminatePseudoState.h"
#include "UmlClass.h"
#include "UmlState.h"
//Added by qt3to4:
#include <QByteArray>

void UmlTerminatePseudoState::generate(UmlClass *, UmlClass *, UmlState *, QByteArray & body, QByteArray indent)
{
    body += indent + "stm._final();\n";
}

