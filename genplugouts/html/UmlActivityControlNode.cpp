
#include "UmlCom.h"
#include "UmlActivityControlNode.h"
//Added by qt3to4:
#include <Q3CString>

void UmlActivityControlNode::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    define();

    UmlCom::message(name());

    Q3CString s = sKind();

    s.replace(0, 1, s.left(1).upper());
    UmlItem::html(s, (UmlDiagram *) 0);

    fw.write("<p>Defined in ");
    parent()->write();
    fw.write("</p>");

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

