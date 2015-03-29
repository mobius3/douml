
#include "UmlDeploymentView.h"
//Added by qt3to4:
#include <QByteArray>

void UmlDeploymentView::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlItem::html(pfix, rank, "Deployment View", level, "view");

    unload(FALSE, FALSE);
}

QByteArray UmlDeploymentView::sKind()
{
    return "deployment view";
}

bool UmlDeploymentView::chapterp()
{
    return TRUE;
}

