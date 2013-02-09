#ifndef _UMLBASESTATEACTION_H
#define _UMLBASESTATEACTION_H


#include "UmlItem.h"
#include "anItemKind.h"
#include <q3cstring.h>

class UmlStateAction;

class UmlBaseStateAction : public UmlItem
{
public:
    // returns a new state action created under 'parent'
    //
    // In case it cannot be created ('parent' cannot contain it etc ...)
    // return 0 in C++ and produce a RuntimeException in Java

    static UmlStateAction * create(UmlItem * parent);

    // returns the kind of the item
    virtual anItemKind kind();


protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseStateAction(void * id, const Q3CString & s) : UmlItem(id, s) {
    }


public:
    // return the expression in OCL
    const Q3CString & expression();

    // set the expression in OCL
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_Expression(const char * s);

#ifdef WITHCPP
    // return the expression in C++
    const Q3CString & cppExpression();

    // set the expression in C++
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppExpression(const char * s);
#endif

#ifdef WITHJAVA
    // return the expression in Java
    const Q3CString & javaExpression();

    // set the expression in Java
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaExpression(const char * s);
#endif

    // to unload the object to free memory, it will be reloaded automatically
    // if needed. Recursively done for the sub items if 'rec' is TRUE.
    //
    // if 'del' is true the sub items are deleted in C++, and removed from the
    // internal dictionnary in C++ and Java (to allow it to be garbaged),
    // you will have to call Children() to re-access to them
    virtual void unload(bool = FALSE, bool = FALSE);


private:
    Q3CString _uml;

#ifdef WITHCPP
    Q3CString _cpp;
#endif

#ifdef WITHJAVA
    Q3CString _java;
#endif


protected:
    virtual void read_uml_();

#ifdef WITHCPP
    virtual void read_cpp_();
#endif

#ifdef WITHJAVA
    virtual void read_java_();
#endif

};

#endif
