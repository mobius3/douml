
#include "UmlBaseDiagram.h"

#include "UmlCom.h"
//Added by qt3to4:

bool UmlBaseDiagram::saveIn(const WrapperStr & s) const
{
    UmlCom::send_cmd(_identifier, saveInCmd, (const char *)s);
    return UmlCom::read_bool();
}

