
#include "UmlTypeSpec.h"
#include "UmlClass.h"
//Added by qt3to4:
#include <QByteArray>

const QByteArray & UmlTypeSpec::toString() const
{
    return (type) ? type->name() : explicit_type;
}

