
#include "UmlClassView.h"
//Added by qt3to4:
#include <QByteArray>

QByteArray UmlClassView::sKind()
{
    return "class view";
}

void UmlClassView::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Class View", level, "view");

    unload(FALSE, FALSE);
}

bool UmlClassView::chapterp()
{
    return TRUE;
}

