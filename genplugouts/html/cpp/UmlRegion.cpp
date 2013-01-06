
#include "UmlRegion.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlRegion::sKind()
{
    return "region";
}

void UmlRegion::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "State region", level, "stateregion");

    unload(FALSE, FALSE);
}

bool UmlRegion::chapterp()
{
    return TRUE;
}

