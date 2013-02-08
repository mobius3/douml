#include <QTextStream>
//Added by qt3to4:
#include "misc/mystr.h"
#include <QTextStream>

#include "UmlTypeSpec.h"
#include "UmlClass.h"

void UmlTypeSpec::generate_require_onces(QTextStream & f,
        WrapperStr & made,
        UmlArtifact * using_art) const
{
    if (type != 0)
        type->generate_require_onces(f, made, using_art);
}
