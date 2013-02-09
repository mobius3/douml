#ifndef _IDLSETTINGS_H
#define _IDLSETTINGS_H

#ifdef WITHIDL


#include <q3cstring.h>
#include "UmlSettings.h"
#include <q3dict.h>

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
    static Q3CString type(Q3CString s);

    // set the IDL type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(Q3CString s, Q3CString v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the IDL type given in argument
    static Q3CString umlType(Q3CString s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString relationStereotype(const Q3CString & s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationStereotype(Q3CString s, Q3CString v);

    // reverse of the RelationStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static Q3CString relationUmlStereotype(Q3CString s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString classStereotype(Q3CString s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(Q3CString s, Q3CString v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static Q3CString classUmlStereotype(Q3CString s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    static Q3CString include(Q3CString s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(Q3CString s, Q3CString v);

    // returns the 'root' directory
    static const Q3CString & rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(Q3CString v);

    // returns the default source file content
    static const Q3CString & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(Q3CString v);

    // returns the extension of the files produced by the Idl code generator
    static const Q3CString & sourceExtension();

    // set the extension of the files produced by the Idl code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(Q3CString v);

    // returns the default definition of an interface
    static const Q3CString & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(Q3CString v);

    // returns the default definition of a valuetype
    static const Q3CString & valuetypeDecl();

    // set the default definition of a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeDecl(Q3CString v);

    // returns the default specification for an 'external' class
    static const Q3CString & externalClassDecl();

    // set the default specification for an 'external' class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExternalClassDecl(Q3CString v);

    // returns the default definition of a struct
    static const Q3CString & structDecl();

    // set the default definition of a struct
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_StructDecl(Q3CString v);

    // returns the default definition of a typedef
    static const Q3CString & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(Q3CString v);

    // returns the default definition of an exception
    static const Q3CString & exceptionDecl();

    // set the default definition of an exception
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExceptionDecl(Q3CString v);

    // returns the default definition of an union
    static const Q3CString & unionDecl();

    // set the default definition of an union
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionDecl(Q3CString v);

    // returns the default definition of an enum
    static const Q3CString & enumDecl();

    // set the default definition of an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(Q3CString v);

    // returns the default definition of an attribute
    static const Q3CString & attributeDecl();

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(Q3CString v);

    // returns the default definition of an attribute
    // placed in a valuetype
    static const Q3CString & valuetypeAttributeDecl();

    // set the default definition of an attribute
    // placed in a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeAttributeDecl(Q3CString v);

    // returns the default definition of an union item
    static const Q3CString & unionItemDecl();

    // set the default definition of an union item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionItemDecl(Q3CString v);

    // returns the default definition of an enumeration item
    static const Q3CString & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(Q3CString v);

    // returns the default definition of a constant attribute
    static const Q3CString & constDecl();

    // set the default definition of a constant attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ConstDecl(Q3CString v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const Q3CString & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    static const Q3CString & valuetypeRelationDecl(const char * multiplicity);

    // set the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeRelationDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    static const Q3CString & unionRelationDecl(const char * multiplicity);

    // set the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionRelationDecl(const char * multiplicity, Q3CString v);

    // returns the default declaration of an operation
    static const Q3CString & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(Q3CString v);

    // returns the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    static const Q3CString & getName();

    // set the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(Q3CString v);

    // returns the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static const Q3CString & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(Q3CString v);

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

    static Q3CString _root;

    static Q3CString _interface_decl;

    static Q3CString _valuetype_decl;

    static Q3CString _struct_decl;

    static Q3CString _typedef_decl;

    static Q3CString _exception_decl;

    static Q3CString _union_decl;

    static Q3CString _enum_decl;

    static Q3CString _external_class_decl;

    static Q3CString _attr_decl;

    static Q3CString _valuetype_attr_decl;

    static Q3CString _union_item_decl;

    static Q3CString _enum_item_decl;

    static Q3CString _const_decl;

    static Q3CString _rel_decl[3/*multiplicity*/];

    static Q3CString _valuetype_rel_decl[3/*multiplicity*/];

    static Q3CString _union_rel_decl[3/*multiplicity*/];

    static Q3CString _oper_decl;

    static Q3CString _get_name;

    static Q3CString _set_name;

    static bool _is_set_oneway;

    static Q3CString _src_content;

    static Q3CString _ext;

    static Q3Dict<Q3CString> _map_includes;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
