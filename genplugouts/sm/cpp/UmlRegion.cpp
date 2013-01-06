
#include "UmlRegion.h"
#include "UmlClass.h"

#include "UmlState.h"
//Added by qt3to4:
#include <Q3CString>

void UmlRegion::init(UmlClass * mother, Q3CString path, Q3CString pretty_path, UmlState *)
{
    const Q3PtrVector<UmlItem> ch = children();
    unsigned index;

    pretty_path = pretty_path + "." + name();

    for (index = 0; index != ch.count(); index += 1)
        if (ch[index]->kind() == aState)
            ((UmlState *) ch[index])->init(mother, path, pretty_path, 0);

}

