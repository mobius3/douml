
#include "UmlUseCaseView.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlUseCaseView::sKind()
{
    return "use case view";
}

void UmlUseCaseView::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Use Case View", level, "view");

    unload(FALSE, FALSE);
}

bool UmlUseCaseView::chapterp()
{
    return TRUE;
}

