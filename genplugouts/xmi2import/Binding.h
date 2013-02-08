#ifndef _BINDING_H
#define _BINDING_H


#include <q3ptrlist.h>


class FileIn;
class Token;
class UmlClass;

//Manages template actuals

class Binding
{
public:
    static void import(FileIn & in, Token & token, UmlClass * where);

    static void solveThem();


protected:
    static Q3PtrList<Binding> All;

    //xmiId of the class having the binbing
    WrapperStr boundId;

    //xmiId of the formal
    WrapperStr formalId;

    //xmiId of the actual, may be a class, or an opaque expression
    WrapperStr actualId;

    //the actual if actualId is empty
    WrapperStr actual;

    //xmiId of the signature

    WrapperStr signatureId;

};

#endif
