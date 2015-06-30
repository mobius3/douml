
#include "UmlTypeSpec.h"
#include "UmlClass.h"

const QByteArray & UmlTypeSpec::toString() const {
  return (type) ? type->name() : explicit_type;
}

