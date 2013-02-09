
#include "UmlInterruptibleActivityRegion.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlInterruptibleActivityRegion::sKind()
{
    return "interruptible activity region";
}

void UmlInterruptibleActivityRegion::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Interruptible activity region", level, "interruptibleactivityregion");

    unload(FALSE, FALSE);
}

