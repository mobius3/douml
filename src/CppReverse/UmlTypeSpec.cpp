
#include "UmlTypeSpec.h"

#ifdef ROUNDTRIP
#include "UmlClass.h"
#include "CppSettings.h"
//Added by qt3to4:
#include <Q3CString>

static inline bool eq(const Q3CString & s1, const Q3CString s2)
{
  return (s1.isEmpty()) ? s2.isEmpty() : (s1 == s2);
}

bool UmlTypeSpec::equal(const UmlTypeSpec & other) const {
  if (type != 0) {
    if (other.type == type)
      return TRUE;
    else if (other.type != 0)
      return FALSE;
    else
      return (type->name() ==
	      CppSettings::type(other.explicit_type));
  }
  else {
    if (other.type == 0)
      return (eq(CppSettings::type(explicit_type),
		 CppSettings::type(other.explicit_type)));
    else
      return (other.type->name() ==
	      CppSettings::type(explicit_type));
  }
}
#endif

