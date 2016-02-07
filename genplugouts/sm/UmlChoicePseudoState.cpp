
#include "UmlChoicePseudoState.h"
#include "UmlClass.h"
#include "UmlState.h"

#include "UmlTransition.h"
//Added by qt3to4:
#include <QByteArray>

void UmlChoicePseudoState::generate(UmlClass * machine, UmlClass * anystate, UmlState * state, QByteArray & body, QByteArray indent)
{
    const QVector<UmlItem*> ch = children();
    QList<UmlTransition*> trs;
    int index;

    for (index = 0; index != ch.count(); index += 1)
        if (ch[index]->kind() == aTransition)
            // theo mandatory
            trs.append((UmlTransition *) ch[index]);

    UmlTransition::generate(trs, machine, anystate, state, body, indent, FALSE);
}

