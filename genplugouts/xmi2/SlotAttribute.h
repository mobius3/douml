#ifndef _SLOTATTRIBUTE_H
#define _SLOTATTRIBUTE_H




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
