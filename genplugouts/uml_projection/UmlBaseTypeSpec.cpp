
#include "UmlBaseTypeSpec.h"
#include "UmlClass.h"
//Added by qt3to4:
#include <QByteArray>

const QByteArray & UmlBaseTypeSpec::toString() const
{
    return (type) ? type->name() : explicit_type;
}

