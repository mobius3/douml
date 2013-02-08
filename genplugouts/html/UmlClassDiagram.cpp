
#include "UmlClassDiagram.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlClassDiagram::sKind()
{
    return "class diagram";
}

void UmlClassDiagram::memo_ref()
{
    diagrams.addElement(this);
    UmlDiagram::memo_ref();
}

void UmlClassDiagram::ref_index()
{
    if (!diagrams.isEmpty())
        fw.write("<a href=\"classdiagrams.html\" target = \"projectFrame\"><b> -Class Diagrams- </b></a>");
}

void UmlClassDiagram::generate_index()
{
    UmlItem::generate_index(diagrams, "Class Diagram", "classdiagrams");
}

Vector UmlClassDiagram::diagrams;

