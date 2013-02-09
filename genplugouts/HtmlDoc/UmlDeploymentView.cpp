
#include "UmlDeploymentView.h"
//Added by qt3to4:
#include <Q3CString>

void UmlDeploymentView::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Deployment View", level, "view");

    unload(FALSE, FALSE);
}

Q3CString UmlDeploymentView::sKind()
{
    return "deployment view";
}

bool UmlDeploymentView::chapterp()
{
    return TRUE;
}

