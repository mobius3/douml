
#include "UmlOnSignalAction.h"
//Added by qt3to4:
#include <Q3CString>

void UmlOnSignalAction::html(Q3CString pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    Q3CString s = signal();
    Q3CString scpp = cppSignal();
    Q3CString sjava = javaSignal();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Signal :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

