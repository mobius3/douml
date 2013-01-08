
#include "UmlBaseDiagram.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <Q3CString>
bool UmlBaseDiagram::saveIn(const Q3CString & s) const
{
    UmlCom::send_cmd(_identifier, saveInCmd, (const char *)s); //[rageek] Fix prototype
    return UmlCom::read_bool();
}

