#ifndef _IDLSETTINGS_H
#define _IDLSETTINGS_H

#ifdef WITHIDL



#include "UmlSettings.h"


// This class manages settings concerning IDL, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'IdlSettings::member' rather than
// 'IdlSettings::instance()->member' or other long sentence like this.
class IdlSettings : public UmlSettings
{
public:
    // returns TRUE when the created Java objects are initialized
    // with the default declaration/definition
    static bool useDefaults();

    // if y is TRUE the future created Java objects will be initialized
    // with the default declaration/definition
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_UseDefaults(bool y);

    // returns the IDL type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    static QByteArray type(QByteArray s);

    // set the IDL type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(QByteArray s, QByteArray v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the IDL type given in argument
    static QByteArray umlType(QByteArray s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray relationAttributeStereotype(const QByteArray & s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(QByteArray s, QByteArray v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static QByteArray relationAttributeUmlStereotype(QByteArray s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray classStereotype(QByteArray s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(QByteArray s, QByteArray v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static QByteArray classUmlStereotype(QByteArray s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    static QByteArray include(QByteArray s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(QByteArray s, QByteArray v);

    // returns the 'root' directory
    static const QByteArray & rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(QByteArray v);

    // returns the default source file content
    static const QByteArray & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(QByteArray v);

    // returns the extension of the files produced by the Idl code generator
    static const QByteArray & sourceExtension();

    // set the extension of the files produced by the Idl code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(QByteArray v);

    // returns the default definition of an interface
    static const QByteArray & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(QByteArray v);

    // returns the default definition of a valuetype
    static const QByteArray & valuetypeDecl();

    // set the default definition of a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeDecl(QByteArray v);

    // returns the default specification for an 'external' class
    static const QByteArray & externalClassDecl();

    // set the default specification for an 'external' class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExternalClassDecl(QByteArray v);

    // returns the default definition of a struct
    static const QByteArray & structDecl();

    // set the default definition of a struct
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_StructDecl(QByteArray v);

    // returns the default definition of a typedef
    static const QByteArray & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(QByteArray v);

    // returns the default definition of an exception
    static const QByteArray & exceptionDecl();

    // set the default definition of an exception
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExceptionDecl(QByteArray v);

    // returns the default definition of an union
    static const QByteArray & unionDecl();

    // set the default definition of an union
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionDecl(QByteArray v);

    // returns the default definition of an enum
    static const QByteArray & enumDecl();

    // set the default definition of an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(QByteArray v);

    // returns the default definition of an attribute depending on the multiplicity
    static const QByteArray & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an attribute
    // placed in a valuetype depending on the multiplicity
    static const QByteArray & valuetypeAttributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    // placed in a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeAttributeDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an union item depending on the multiplicity
    static const QByteArray & unionItemDecl(const char * multiplicity);

    // set the default definition of an union item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionItemDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an enumeration item
    static const QByteArray & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(QByteArray v);

    // returns the default definition of a constant attribute depending on the multiplicity
    static const QByteArray & constDecl(const char * multiplicity);

    // set the default definition of a constant attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ConstDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const QByteArray & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    static const QByteArray & valuetypeRelationDecl(const char * multiplicity);

    // set the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeRelationDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    static const QByteArray & unionRelationDecl(const char * multiplicity);

    // set the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionRelationDecl(const char * multiplicity, QByteArray v);

    // returns the default declaration of an operation
    static const QByteArray & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(QByteArray v);

    // returns the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    static const QByteArray & getName();

    // set the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(QByteArray v);

    // returns the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static const QByteArray & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(QByteArray v);

    // returns if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is oneway by default
    static bool isSetOneway();

    // set if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is oneway by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetOneway(bool v);


private:
    // never called !
    IdlSettings() {};

    static bool _defined;

    static QByteArray _root;

    static QByteArray _interface_decl;

    static QByteArray _valuetype_decl;

    static QByteArray _struct_decl;

    static QByteArray _typedef_decl;

    static QByteArray _exception_decl;

    static QByteArray _union_decl;

    static QByteArray _enum_decl;

    static QByteArray _external_class_decl;

    static QByteArray _attr_decl[3/*multiplicity*/];

    static QByteArray _valuetype_attr_decl[3/*multiplicity*/];

    static QByteArray _union_item_decl[3/*multiplicity*/];

    static QByteArray _enum_item_decl;

    static QByteArray _const_decl[3/*multiplicity*/];

    static QByteArray _rel_decl[3/*multiplicity*/];

    static QByteArray _valuetype_rel_decl[3/*multiplicity*/];

    static QByteArray _union_rel_decl[3/*multiplicity*/];

    static QByteArray _oper_decl;

    static QByteArray _get_name;

    static QByteArray _set_name;

    static bool _is_set_oneway;

    static QByteArray _src_content;

    static QByteArray _ext;

    static QHash<QByteArray, QByteArray*> _map_includes;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif
