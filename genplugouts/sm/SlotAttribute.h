#ifndef _SLOTATTRIBUTE_H
#define _SLOTATTRIBUTE_H


#include <QByteArray>

class UmlAttribute;

struct SlotAttribute {
    UmlAttribute * attribute;

    QByteArray value;

    // because of QValueList use
    SlotAttribute() : attribute(0) {
    }

    SlotAttribute(UmlAttribute * a, QByteArray v) : attribute(a), value(v) {
    }

};

#endif
