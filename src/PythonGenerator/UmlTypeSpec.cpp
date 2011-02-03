
#include <q3textstream.h> 
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

#include "UmlTypeSpec.h"
#include "UmlClass.h"

void UmlTypeSpec::generate_import(QTextOStream & f, UmlArtifact * using_art, 
				  bool from, Q3CString & made) const {
  if (type != 0)
    type->generate_import(f, using_art, from, made);
}


