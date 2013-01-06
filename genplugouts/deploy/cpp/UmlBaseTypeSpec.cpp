
#include "UmlBaseTypeSpec.h"
#include "UmlClass.h"
//Added by qt3to4:
#include <Q3CString>

const Q3CString & UmlBaseTypeSpec::toString() const
{
    return (type) ? type->name() : explicit_type;
}

