
#include "UmlActivityPin.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlActivityPin::sKind()
{
    return "activity action pin";
}

void UmlActivityPin::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    define();

    fw.write("<table><tr><td><div class=\"element\">Activity action pin <b>");
    writeq(name());
    fw.write("</b></div></td></tr></table>\n");

    UmlPinParameter::html(pfix, rank, level);

    unload(FALSE, FALSE);
}

