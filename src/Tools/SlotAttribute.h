#ifndef _SLOTATTRIBUTE_H
#define _SLOTATTRIBUTE_H


#include "misc/mystr.h"

class UmlAttribute;

struct SlotAttribute {
    UmlAttribute * attribute;

    WrapperStr value;

    // because of QValueList use
    SlotAttribute() : attribute(0) {
    }

    SlotAttribute(UmlAttribute * a, WrapperStr v) : attribute(a), value(v) {
    }

};

#endif
