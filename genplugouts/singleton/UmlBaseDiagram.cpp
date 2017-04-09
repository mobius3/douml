
#include "UmlBaseDiagram.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>
bool UmlBaseDiagram::saveIn(const QByteArray & s) const
{
    UmlCom::send_cmd(_identifier, saveInCmd, (const char *)s); //[jasa] ambiguous call
    return UmlCom::read_bool();
}

