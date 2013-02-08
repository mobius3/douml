#ifndef _UMLBASETYPESPEC_H
#define _UMLBASETYPESPEC_H




class UmlClass;

// this class memorize a type specification, which may be
//
// - a class reference
//
// - an explicit type
class UmlBaseTypeSpec
{
public:
    UmlBaseTypeSpec() : type(0) {};

    // returns the type as a string in all cases
    const WrapperStr & toString() const;

    // significant in case type == 0
    WrapperStr explicit_type;

    UmlClass * type;

};

#endif
