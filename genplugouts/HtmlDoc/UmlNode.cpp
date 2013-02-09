
#include "UmlNode.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <Q3CString>
Q3CString UmlNode::sKind()
{
    return "node";
}

void UmlNode::html(Q3CString, unsigned int, unsigned int)
{
    UmlCom::message(name());

    UmlItem::html("Node", (UmlDiagram *) associatedDiagram());

    unload(FALSE, FALSE);
}

