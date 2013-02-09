
#include "UmlBaseTypeSpec.h"
#include "UmlClass.h"
//Added by qt3to4:
#include "misc/mystr.h"

const WrapperStr & UmlBaseTypeSpec::toString() const
{
    return (type) ? type->name() : explicit_type;
}

