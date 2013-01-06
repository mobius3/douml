
#include "UmlAccessVariableValueAction.h"
//Added by qt3to4:
#include <Q3CString>

void UmlAccessVariableValueAction::html(Q3CString pfix, unsigned int rank, unsigned int level)
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

