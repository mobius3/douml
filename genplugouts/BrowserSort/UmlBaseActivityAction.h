#ifndef _UMLBASEACTIVITYACTION_H
#define _UMLBASEACTIVITYACTION_H


#include "UmlActivityNode.h"


class UmlDiagram;

class UmlBaseActivityAction : public UmlActivityNode
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseActivityAction(void * id, const QByteArray & s) : UmlActivityNode(id, s) {
    }


public:
    // return the pre condition
    const QByteArray & preCondition();

    // set the pre condition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PreCondition(const char * v);

    // return the post condition
    const QByteArray & postCondition();

    // set the post condition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PostCondition(const char * v);

#ifdef WITHCPP
    // return the pre condition in C++
    const QByteArray & cppPreCondition();

    // set the pre condition in C++
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppPreCondition(const char * v);

    // return the post condition in C++
    const QByteArray & cppPostCondition();

    // set the post condition in C++
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppPostCondition(const char * v);
#endif

#ifdef WITHJAVA
    // return the pre condition in Java
    const QByteArray & javaPreCondition();

    // set the pre condition in Java
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaPreCondition(const char * v);

    // return the post condition in Java
    const QByteArray & javaPostCondition();

    // set the post condition in Java
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaPostCondition(const char * v);
#endif

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
    virtual void unload(bool = FALSE, bool = FALSE) override;


private:
    QByteArray _pre_condition;

    QByteArray _post_condition;

#ifdef WITHCPP
    QByteArray _cpp_pre_condition;

    QByteArray _cpp_post_condition;
#endif

#ifdef WITHJAVA
    QByteArray _java_pre_condition;

    QByteArray _java_post_condition;
#endif

    UmlDiagram * _assoc_diagram;


protected:
    virtual void read_uml_() override;

#ifdef WITHCPP
    virtual void read_cpp_() override;
#endif

#ifdef WITHJAVA
    virtual void read_java_() override;
#endif

};

#endif
