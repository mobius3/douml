
#include "UmlExpansionRegion.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlExpansionRegion::sKind()
{
    return "expansion region";
}

void UmlExpansionRegion::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Expansion region", level, "expansionregion");

    unload(FALSE, FALSE);
}

