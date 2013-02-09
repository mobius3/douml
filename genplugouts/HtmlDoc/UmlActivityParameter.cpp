
#include "UmlActivityParameter.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlActivityParameter::sKind()
{
    return "activity parameter";
}

void UmlActivityParameter::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    define();

    fw.write("<table><tr><td><div class=\"element\">Activity action pin <b>");
    writeq(name());
    fw.write("</b></div></td></tr></table>\n");

    Q3CString s = defaultValue();

    if (! s.isEmpty()) {
        fw.write("<p>Default value :</p><ul>");

        fw.write("<pre>\n");
        writeq(s);
        fw.write("</pre></ul>");
    }

    UmlPinParameter::html(pfix, rank, level);

    unload(FALSE, FALSE);
}

