#include <q3textstream.h> 
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

#include "UmlTypeSpec.h"
#include "UmlClass.h"

void UmlTypeSpec::generate_require_onces(QTextOStream & f,
					 Q3CString & made,
					 UmlArtifact * using_art) const {
  if (type != 0)
    type->generate_require_onces(f, made, using_art);
}
