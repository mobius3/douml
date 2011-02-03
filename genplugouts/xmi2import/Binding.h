#ifndef _BINDING_H
#define _BINDING_H


#include <q3ptrlist.h>
#include <q3cstring.h>

class FileIn;
class Token;
class UmlClass;

//Manages template actuals

class Binding {
  public:
    static void import(FileIn & in, Token & token, UmlClass * where);

    static void solveThem();


  protected:
    static Q3PtrList<Binding> All;

    //xmiId of the class having the binbing
    Q3CString boundId;

    //xmiId of the formal
    Q3CString formalId;

    //xmiId of the actual, may be a class, or an opaque expression
    Q3CString actualId;

    //the actual if actualId is empty
    Q3CString actual;

    //xmiId of the signature
    
    Q3CString signatureId;

};

#endif
