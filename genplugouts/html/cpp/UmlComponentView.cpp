
#include "UmlComponentView.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlComponentView::sKind()
{
    return "component view";
}

void UmlComponentView::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Component View", level, "view");

    unload(FALSE, FALSE);
}

bool UmlComponentView::chapterp()
{
    return TRUE;
}

