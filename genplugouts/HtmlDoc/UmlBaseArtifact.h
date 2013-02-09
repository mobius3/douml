#ifndef _UMLBASEARTIFACT_H
#define _UMLBASEARTIFACT_H


#include "UmlItem.h"
#include "anItemKind.h"
#include <q3ptrvector.h>
#include <q3cstring.h>

#include "UmlClass.h"	// to avoid destructor problem
class UmlArtifact;
class UmlDeploymentView;
class UmlDeploymentDiagram;
class UmlClass;

//Manage the artifacts
class UmlBaseArtifact : public UmlItem
{
public:
    // returns a new artifact named 'name' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlArtifact * create(UmlDeploymentView * parent, const char * s);

    // returns the kind of the item
    virtual anItemKind kind();

    // returns the optional associated diagram
    UmlDeploymentDiagram * associatedDiagram();

    // sets the associated diagram, arg may be null to unset it
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedDiagram(UmlDeploymentDiagram * d);

    // returns (in Java a copy of) the optional associated classes
    // significant when the artifact is stereotyped <<source>>
    const Q3PtrVector<UmlClass> & associatedClasses();

    // adds 'cl' at the end of the associated classes list, returns false
    // if 'cl' is already an associate class.
    // significant when the artifact is stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool addAssociatedClass(UmlClass * cl);

    // removes an associated class
    // significant when the artifact is not stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool removeAssociatedClass(UmlClass * cl);

    // set the associated classes list
    // significant when the artifact is stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_AssociatedClasses(const Q3PtrVector<UmlClass> & l);

    // returns (in Java a copy of) the associated artifacts list
    // significant when the artifact is not stereotyped <<source>>
    const Q3PtrVector<UmlArtifact> & associatedArtifacts();

    // adds an associated artifacts, returns false if 'cp' is already
    // an associate artifact.
    // significant when the artifact is not stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool addAssociatedArtifact(UmlArtifact * cp);

    // removes an associated artifacts
    // significant when the artifact is not stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool removeAssociatedArtifact(UmlArtifact * cp);

    // removes all associated artifacts
    // significant when the artifact is not stereotyped <<source>>
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool removeAllAssociatedArtifacts();

#ifdef WITHCPP
    // returns the C++ header file definition
    const Q3CString & cppHeader();

    // to set the C++ header file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppHeader(const Q3CString & s);

    // returns the C++ source file definition
    const Q3CString & cppSource();

    // to set the C++ source file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppSource(const Q3CString & s);
#endif

#ifdef WITHJAVA
    // returns the Java file definition
    const Q3CString & javaSource();

    // to set the Java file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaSource(const Q3CString & s);
#endif

#ifdef WITHPHP
    // returns the Php file definition
    const Q3CString & phpSource();

    // to set the Php file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PhpSource(const Q3CString & s);
#endif

#ifdef WITHPYTHON
    // returns the Python file definition
    const Q3CString & pythonSource();

    // to set the Python file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PythonSource(const Q3CString & s);
#endif

#ifdef WITHIDL
    // returns the Idl file definition
    const Q3CString & idlSource();

    // to set the Idl file definition
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_IdlSource(const Q3CString & s);
#endif

    // to unload the object to free memory, it will be reloaded
    // automatically if needed. args unused
    virtual void unload(bool = FALSE, bool = FALSE);


private:
    UmlDeploymentDiagram * _assoc_diagram;

    Q3PtrVector<UmlClass> _assoc_classes;

    Q3PtrVector<UmlArtifact> _associated;

#ifdef WITHCPP
    Q3CString _cpp_h;

    Q3CString _cpp_src;
#endif

#ifdef WITHJAVA
    Q3CString _java_src;
#endif

#ifdef WITHPHP
    Q3CString _php_src;
#endif

#ifdef WITHPYTHON
    Q3CString _python_src;
#endif

#ifdef WITHIDL
    Q3CString _idl_src;
#endif


protected:
    virtual void read_uml_();

#ifdef WITHCPP
    virtual void read_cpp_();
#endif

#ifdef WITHJAVA
    virtual void read_java_();
#endif

#ifdef WITHPHP
    virtual void read_php_();
#endif

#ifdef WITHPYTHON
    //internal, do NOT use it

    virtual void read_python_();
#endif

#ifdef WITHIDL
    virtual void read_idl_();
#endif

    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseArtifact(void * id, const Q3CString & n);

    friend class UmlBaseClass;
};

inline UmlBaseArtifact::UmlBaseArtifact(void * id, const Q3CString & n) : UmlItem(id, n)
{
    _assoc_diagram = 0;
}

#endif
