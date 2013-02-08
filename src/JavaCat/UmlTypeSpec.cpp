
#include "UmlTypeSpec.h"

#ifdef ROUNDTRIP
#include "UmlClass.h"
#include "JavaSettings.h"
//Added by qt3to4:
#include "misc/mystr.h"

static inline bool eq(const WrapperStr & s1, const WrapperStr s2)
{
    return (s1.isEmpty()) ? s2.isEmpty() : (s1 == s2);
}

bool UmlTypeSpec::equal(const UmlTypeSpec & other) const
{
    if (type != 0) {
        if (other.type == type)
            return TRUE;
        else if (other.type != 0)
            return FALSE;
        else
            return (type->name() ==
                    JavaSettings::type(other.explicit_type));
    }
    else {
        if (other.type == 0)
            return (eq(JavaSettings::type(explicit_type),
                       JavaSettings::type(other.explicit_type)));
        else
            return (other.type->name() ==
                    JavaSettings::type(explicit_type));
    }
}
#endif

