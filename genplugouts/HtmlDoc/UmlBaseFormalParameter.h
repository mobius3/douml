#ifndef _UMLBASEFORMALPARAMETER_H
#define _UMLBASEFORMALPARAMETER_H



#include "UmlTypeSpec.h"

// This class manages 'formal parameters' of a template class. For instance 'T' in
//
//	template class Cl<class T> ...
class UmlBaseFormalParameter
{
public:
    UmlBaseFormalParameter() {};

    // returns the name of the formal
    const QByteArray & name() const {
        return _name;
    };

    // returns the type of a formal, probably "class"
    const QByteArray & type() const {
        return _type;
    };

    // returns the default actual value
    const UmlTypeSpec & defaultValue() const {
        return _default_value;
    };

    //  return the optional extend (Java)
    const UmlTypeSpec & extend() {
        return _extends;
    };

protected:
    QByteArray _name;

    // "class" ...
    QByteArray _type;

    UmlTypeSpec _default_value;

    UmlTypeSpec _extends;

    void read_();

    friend class UmlBaseClass;
};

#endif
