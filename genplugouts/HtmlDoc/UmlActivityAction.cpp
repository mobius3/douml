
#include "UmlActivityAction.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>
void UmlActivityAction::html()
{
    UmlCom::message(name());

    QByteArray s = sKind();

    s.replace(0, 1, s.left(1).toUpper());

    UmlItem::html(s, (UmlDiagram *) associatedDiagram());

    fw.write("<p>Defined in ");
    parent()->write();
    fw.write("</p>");

    QByteArray scpp, sjava;

    s = preCondition();
    scpp = cppPreCondition();
    sjava = javaPreCondition();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Pre Condition :</p><ul>");

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

    s = postCondition();
    scpp = cppPostCondition();
    sjava = javaPostCondition();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Post Condition :</p><ul>");

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

    if (! constraint().isEmpty()) {
        fw.write("<p> Constraint :</p><ul>");
        writeq(constraint());
        fw.write("</ul>");
    }
}

