
#include "UmlInterruptibleActivityRegion.h"
//Added by qt3to4:
#include <QByteArray>

QByteArray UmlInterruptibleActivityRegion::sKind()
{
    return "interruptible activity region";
}

void UmlInterruptibleActivityRegion::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Interruptible activity region", level, "interruptibleactivityregion");

    unload(FALSE, FALSE);
}

