
#include "UmlUseCaseView.h"
//Added by qt3to4:
#include <QByteArray>

QByteArray UmlUseCaseView::sKind()
{
    return "use case view";
}

void UmlUseCaseView::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Use Case View", level, "view");

    unload(FALSE, FALSE);
}

bool UmlUseCaseView::chapterp()
{
    return TRUE;
}

