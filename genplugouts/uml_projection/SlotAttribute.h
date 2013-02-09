#ifndef _SLOTATTRIBUTE_H
#define _SLOTATTRIBUTE_H


#include <q3cstring.h>

class UmlAttribute;

struct SlotAttribute {
    UmlAttribute * attribute;

    Q3CString value;

    // because of QValueList use
    SlotAttribute() : attribute(0) {
    }

    SlotAttribute(UmlAttribute * a, Q3CString v) : attribute(a), value(v) {
    }

};

#endif
