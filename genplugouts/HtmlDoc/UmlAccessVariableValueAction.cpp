
#include "UmlAccessVariableValueAction.h"
//Added by qt3to4:
#include <QByteArray>

void UmlAccessVariableValueAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (variable() != 0) {
        fw.write("<p>Variable : ");
        variable()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

