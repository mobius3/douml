
#include "UmlCom.h"
#include "UmlStateAction.h"
//Added by qt3to4:
#include <QByteArray>

QByteArray UmlStateAction::sKind()
{
    return "state action";
}

void UmlStateAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlCom::message(name());

    QByteArray s = stereotype();

    if (s.isEmpty())
        s = "State action";
    else
        s = "State action " + s;

    UmlItem::html(s, (UmlDiagram *) 0);

    fw.write("<p>Defined in ");

    if (parent()->kind() == aRegion)
        parent()->parent()->write();
    else
        parent()->write();

    fw.write("</p>");

    s = expression();

    QByteArray scpp = cppExpression();
    QByteArray sjava = javaExpression();

    if ((!s.isEmpty()) || (!scpp.isEmpty()) || (!sjava.isEmpty())) {
        fw.write("<p>Expression :</p><ul>");

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

