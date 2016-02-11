
#include "UmlRegion.h"
#include "UmlClass.h"

#include "UmlState.h"
//Added by qt3to4:
#include <QByteArray>

void UmlRegion::init(UmlClass * mother, QByteArray path, QByteArray pretty_path, UmlState *)
{
    const QVector<UmlItem*> ch = children();
    int index;

    pretty_path = pretty_path + "." + name();

    for (index = 0; index != ch.count(); index += 1)
        if (ch[index]->kind() == aState)
            ((UmlState *) ch[index])->init(mother, path, pretty_path, 0);

}

