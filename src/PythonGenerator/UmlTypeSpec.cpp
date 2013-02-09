
#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>

#include "UmlTypeSpec.h"
#include "UmlClass.h"

void UmlTypeSpec::generate_import(QTextStream & f, UmlArtifact * using_art,
                                  bool from, WrapperStr & made) const
{
    if (type != 0)
        type->generate_import(f, using_art, from, made);
}


