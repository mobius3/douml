#ifndef _UMLBASEOPERATION_H
#define _UMLBASEOPERATION_H


#include "UmlClassMember.h"
#include "anItemKind.h"
#include "UmlTypeSpec.h"
#include <QList>
#include <QByteArray>

#include "UmlParameter.h"
class UmlOperation;
class UmlClass;
struct UmlParameter;

//  Manage the class's operations
class UmlBaseOperation : public UmlClassMember {
  public:
    // returns a new operation named 'name' created under 'parent'
    //
    // In case it cannot be created (the name is already used or
    // invalid, 'parent' cannot contain it etc ...) return 0 in C++
    // and produce a RuntimeException in Java
    static UmlOperation * create(UmlClass * parent, const char * s);

    // returns the kind of the item
    virtual anItemKind kind();

    // indicates if the operation is abstract, returns TRUE if yes
    bool isAbstract();

    // to set the 'abstract' flag
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isAbstract(bool y);

    // returns the operation value type
    const UmlTypeSpec & returnType();

    // to set the operation value type
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_ReturnType(const UmlTypeSpec & t);

    // returns (in java a copy of) the parameters list
    const QList<UmlParameter> params();

    // adds a parameter at the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool addParameter(unsigned rank, const UmlParameter & p);

    // remove the parameter of the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool removeParameter(unsigned rank);

    // replace the parameter at the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool replaceParameter(unsigned rank, const UmlParameter & p);

    // returns the exceptions
    const QList<UmlTypeSpec> exceptions();

    // adds the exception at the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool addException(unsigned rank, const UmlTypeSpec & t);

    // remove the exception of the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool removeException(unsigned rank);

    // replaces the exception at the given rank (0...)
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool replaceException(unsigned rank, const UmlTypeSpec & t);

    // in case the operation is a 'get' operation, returns the associated
    // attribute or relation
    UmlClassMember * getOf();

    // in case the operation is a 'set' operation, returns the associated
    // attribute or relation
    UmlClassMember * setOf();

#ifdef WITHCPP
    // returns TRUE if the operation is declared const in C++
    bool isCppConst();

    // to set if the operation is declared const in C++
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isCppConst(bool y);

    // returns TRUE if the operation is a friend in C++
    bool isCppFriend();

    // to set if the operation is a friend in C++
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isCppFriend(bool y);

    // returns TRUE if the operation is declared virtual in C++
    bool isCppVirtual();

    // to set if the operation is declared virtual in C++
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isCppVirtual(bool y);

    // returns TRUE if the operation is declared inline in C++
    bool isCppInline();

    // to set if the operation is declared inline in C++
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isCppInline(bool y);

    // returns the operation's definition in C++, notes that the declaration
    // is returned by the inherited ClassItemBase::CppDecl() operation
    const QByteArray & cppDef();

    // sets the operation's definition in C++, notes that the declaration
    // is set through the inherited ClassItemBase::set_CppDecl() operation
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppDef(const char * s);

    // returns the operation's body in C++, useless if the def does not
    // contains ${body}. Note that the body is get each time from DOUML
    // for memory size reason
    QByteArray cppBody();

    // sets the operation's body in C++, useless if the def does not 
    // contains ${body}
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppBody(const char * s);

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's C++ name must be generated
    const QByteArray & cppNameSpec();

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's C++ name must be generated
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_CppNameSpec(const char * s);
#endif

#ifdef WITHJAVA
    // returns TRUE if the operation is declared final in JAVA
    bool isJavaFinal();

    // to set if the operation is declared final in JAVA
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isJavaFinal(bool y);

    // returns TRUE if the operation is declared synchronized in JAVA
    bool isJavaSynchronized();

    // to set if the operation is declared synchronized in JAVA
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isJavaSynchronized(bool y);

    // returns the operation's definition in Java, notes that it is
    // already made by the inherited JavaDecl operation
    const QByteArray & javaDef();

    // sets the operation's definition in Java, notes that it is
    // already made by the inherited set_JavaDecl operation
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaDef(const char * s);

    // returns the operation's body in Java++, useless if the def does
    // not contains ${body} Note that the body is get each time from DOUML
    // for memory size reason
    QByteArray javaBody();

    // sets the operation's body in Java, useless if the def does not 
    // contains ${body}
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaBody(const char * s);

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's JAVA name must be generated
    const QByteArray & javaNameSpec();

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's JAVA name must be generated
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_JavaNameSpec(const char * s);
#endif

#ifdef WITHIDL
    // returns TRUE if the operation is declared oneway in IDL
    bool isIdlOneway();

    // to set if the operation is declared oneway in IDL
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isIdlOneway(bool y);

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's IDL name must be generated
    const QByteArray & idlNameSpec();

    // in case the operation is a 'get' or 'set' operation, returns how
    // the operation's IDL name must be generated
    // 
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_IdlNameSpec(const char * s);
#endif

    // to unload the object to free memory, it will be reloaded
    // automatically if needed. args unused
    virtual void unload(bool = FALSE, bool = FALSE);


  private:
    bool _abstract : 1;

#ifdef WITHCPP
    bool _cpp_const : 1;

    bool _cpp_friend : 1;

    bool _cpp_virtual : 1;

    bool _cpp_inline : 1;
#endif

#ifdef WITHJAVA
    bool _java_final : 1;

    bool _java_synchronized : 1;
#endif

#ifdef WITHPHP
    bool _php_final : 1;
#endif
#ifdef WITHIDL
    bool _idl_oneway : 1;
#endif

#ifdef WITHCPP
    bool _cpp_get_set_frozen : 1;
#endif

#ifdef WITHJAVA
    bool _java_get_set_frozen : 1;
#endif

#ifdef WITHPHP
    bool _php_get_set_frozen : 1;
#endif

#ifdef WITHPYTHON
    bool _python_get_set_frozen : 1;
#endif

#ifdef WITHIDL
    bool _idl_get_set_frozen : 1;
#endif

#ifdef WITHCPP
    bool _cpp_contextual_body_indent : 1;
#endif

#ifdef WITHJAVA
    bool _java_contextual_body_indent : 1;
#endif

#ifdef WITHPHP
    bool _php_contextual_body_indent : 1;
#endif

#ifdef WITHPYTHON
    bool _python_contextual_body_indent : 1;
#endif

    UmlTypeSpec _return_type;

    QList<UmlParameter> _params;

    QList<UmlTypeSpec> _exceptions;

#ifdef WITHCPP
    QByteArray _cpp_def;

    QByteArray _cpp_name_spec;
#endif

#ifdef WITHJAVA
    QByteArray _java_name_spec;
#endif

#ifdef WITHPHP
    QByteArray _php_name_spec;
#endif

#ifdef WITHPYTHON
    QByteArray _python_name_spec;

    QByteArray _python_decorators;
#endif

#ifdef WITHIDL
    QByteArray _idl_name_spec;
#endif

    // exclusive with set_of
    UmlClassMember * _get_of;

    // exclusive with get_of
    UmlClassMember * _set_of;


  protected:
    // the constructor, do not call it yourself !!!!!!!!!!
    UmlBaseOperation(void * id, const QByteArray & n);

    virtual void read_uml_();

#ifdef WITHCPP
    virtual void read_cpp_();
#endif

#ifdef WITHJAVA
    virtual void read_java_();
#endif

#ifdef WITHPHP
    //internal, do NOT use it

    virtual void read_php_();
#endif

#ifdef WITHPYTHON
    //internal, do NOT use it

    virtual void read_python_();
#endif

#ifdef WITHIDL
    virtual void read_idl_();
#endif

};

inline UmlBaseOperation::UmlBaseOperation(void * id, const QByteArray & n) : UmlClassMember(id, n) {
  _get_of = 0;
  _set_of = 0;
}

#endif
