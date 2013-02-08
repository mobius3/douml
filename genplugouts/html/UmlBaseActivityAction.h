#ifndef _UMLBASEACTIVITYACTION_H
#define _UMLBASEACTIVITYACTION_H


#include "UmlActivityNode.h"
#include <q3cstring.h>

class UmlDiagram;

class UmlBaseActivityAction : public UmlActivityNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityAction(void * id, const Q3CString & s) : UmlActivityNode(id, s) {
    }


public:
    // return the pre condition
    const Q3CString & preCondition();

    // set the pre condition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PreCondition(const char * v);

    // return the post condition
    const Q3CString & postCondition();

    // set the post condition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PostCondition(const char * v);

#ifdef WITHCPP
    // return the pre condition in C++
    const Q3CString & cppPreCondition();

    // set the pre condition in C++
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppPreCondition(const char * v);

    // return the post condition in C++
    const Q3CString & cppPostCondition();

    // set the post condition in C++
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppPostCondition(const char * v);
#endif

#ifdef WITHJAVA
    // return the pre condition in Java
    const Q3CString & javaPreCondition();

    // set the pre condition in Java
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaPreCondition(const char * v);

    // return the post condition in Java
    const Q3CString & javaPostCondition();

    // set the post condition in Java
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaPostCondition(const char * v);
#endif

    // return the constraint
    const Q3CString & constraint();

    // set the constraint
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_Constraint(const char * v);

    // returns the optional associated diagram
    UmlDiagram * associatedDiagram();

    // sets the associated diagram, arg may be null to unset it
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedDiagram(UmlDiagram * d);

    // to unload the object to free memory, it will be reloaded automatically
    // if needed. Recursively done for the sub items if 'rec' is TRUE.
    //
    // if 'del' is true the sub items are deleted in C++, and removed from the
    // internal dictionnary in C++ and Java (to allow it to be garbaged),
    // you will have to call Children() to re-access to them
    virtual void unload(bool = FALSE, bool = FALSE);


private:
    Q3CString _pre_condition;

    Q3CString _post_condition;

#ifdef WITHCPP
    Q3CString _cpp_pre_condition;

    Q3CString _cpp_post_condition;
#endif

#ifdef WITHJAVA
    Q3CString _java_pre_condition;

    Q3CString _java_post_condition;
#endif

    Q3CString _constraint;

    UmlDiagram * _assoc_diagram;


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
