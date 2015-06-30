
#include "UmlEntryPointPseudoState.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <QByteArray>
QByteArray UmlEntryPointPseudoState::sKind()
{
    return "entry point pseudo state";
}

void UmlEntryPointPseudoState::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    define();

    UmlCom::message(name());

    QByteArray s = sKind();

    s.replace(0, 1, s.left(1).toUpper());
    UmlItem::html(s, (UmlDiagram *) 0);

    fw.write("<p>Defined in ");

    if (parent()->kind() == aRegion)
        parent()->parent()->write();
    else
        parent()->write();

    fw.write("</p>");

    if (reference() != 0) {
        fw.write("<p>References ");
        reference()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

