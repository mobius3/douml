
#include "UmlStateDiagram.h"
//Added by qt3to4:
#include <QByteArray>

void UmlStateDiagram::memo_ref()
{
    diagrams.addElement(this);
    UmlDiagram::memo_ref();
}

QByteArray UmlStateDiagram::sKind()
{
    return "state diagram";
}

void UmlStateDiagram::ref_index()
{
    if (!diagrams.isEmpty())
        fw.write("<a href=\"statediagrams.html\" target = \"projectFrame\"><b> -State Diagrams- </b></a>");
}

void UmlStateDiagram::generate_index()
{
    UmlItem::generate_index(diagrams, "State Diagram", "statediagrams");
}

Vector UmlStateDiagram::diagrams;

