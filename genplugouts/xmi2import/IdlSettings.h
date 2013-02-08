#ifndef _IDLSETTINGS_H
#define _IDLSETTINGS_H

#ifdef WITHIDL



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
    static WrapperStr type(WrapperStr s);

    // set the IDL type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(WrapperStr s, WrapperStr v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the IDL type given in argument
    static WrapperStr umlType(WrapperStr s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr relationAttributeStereotype(const WrapperStr & s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(WrapperStr s, WrapperStr v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static WrapperStr relationAttributeUmlStereotype(WrapperStr s);

    // returns the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr classStereotype(WrapperStr s);

    // set the IDL stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(WrapperStr s, WrapperStr v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the IDL one given in argument
    static WrapperStr classUmlStereotype(WrapperStr s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    static WrapperStr include(WrapperStr s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the Idl type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(WrapperStr s, WrapperStr v);

    // returns the 'root' directory
    static const WrapperStr & rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(WrapperStr v);

    // returns the default source file content
    static const WrapperStr & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(WrapperStr v);

    // returns the extension of the files produced by the Idl code generator
    static const WrapperStr & sourceExtension();

    // set the extension of the files produced by the Idl code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(WrapperStr v);

    // returns the default definition of an interface
    static const WrapperStr & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(WrapperStr v);

    // returns the default definition of a valuetype
    static const WrapperStr & valuetypeDecl();

    // set the default definition of a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeDecl(WrapperStr v);

    // returns the default specification for an 'external' class
    static const WrapperStr & externalClassDecl();

    // set the default specification for an 'external' class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExternalClassDecl(WrapperStr v);

    // returns the default definition of a struct
    static const WrapperStr & structDecl();

    // set the default definition of a struct
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_StructDecl(WrapperStr v);

    // returns the default definition of a typedef
    static const WrapperStr & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(WrapperStr v);

    // returns the default definition of an exception
    static const WrapperStr & exceptionDecl();

    // set the default definition of an exception
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ExceptionDecl(WrapperStr v);

    // returns the default definition of an union
    static const WrapperStr & unionDecl();

    // set the default definition of an union
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionDecl(WrapperStr v);

    // returns the default definition of an enum
    static const WrapperStr & enumDecl();

    // set the default definition of an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(WrapperStr v);

    // returns the default definition of an attribute depending on the multiplicity
    static const WrapperStr & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an attribute
    // placed in a valuetype depending on the multiplicity
    static const WrapperStr & valuetypeAttributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    // placed in a valuetype
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeAttributeDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an union item depending on the multiplicity
    static const WrapperStr & unionItemDecl(const char * multiplicity);

    // set the default definition of an union item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionItemDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an enumeration item
    static const WrapperStr & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(WrapperStr v);

    // returns the default definition of a constant attribute depending on the multiplicity
    static const WrapperStr & constDecl(const char * multiplicity);

    // set the default definition of a constant attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ConstDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const WrapperStr & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    static const WrapperStr & valuetypeRelationDecl(const char * multiplicity);

    // set the default definition of a relation in a valuetype
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ValuetypeRelationDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    static const WrapperStr & unionRelationDecl(const char * multiplicity);

    // set the default definition of a relation in an union
    // depending on the multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UnionRelationDecl(const char * multiplicity, WrapperStr v);

    // returns the default declaration of an operation
    static const WrapperStr & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(WrapperStr v);

    // returns the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    static const WrapperStr & getName();

    // set the default name of a 'get' operation generated through
    // the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(WrapperStr v);

    // returns the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static const WrapperStr & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(WrapperStr v);

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

    static WrapperStr _root;

    static WrapperStr _interface_decl;

    static WrapperStr _valuetype_decl;

    static WrapperStr _struct_decl;

    static WrapperStr _typedef_decl;

    static WrapperStr _exception_decl;

    static WrapperStr _union_decl;

    static WrapperStr _enum_decl;

    static WrapperStr _external_class_decl;

    static WrapperStr _attr_decl[3/*multiplicity*/];

    static WrapperStr _valuetype_attr_decl[3/*multiplicity*/];

    static WrapperStr _union_item_decl[3/*multiplicity*/];

    static WrapperStr _enum_item_decl;

    static WrapperStr _const_decl[3/*multiplicity*/];

    static WrapperStr _rel_decl[3/*multiplicity*/];

    static WrapperStr _valuetype_rel_decl[3/*multiplicity*/];

    static WrapperStr _union_rel_decl[3/*multiplicity*/];

    static WrapperStr _oper_decl;

    static WrapperStr _get_name;

    static WrapperStr _set_name;

    static bool _is_set_oneway;

    static WrapperStr _src_content;

    static WrapperStr _ext;

    static Q3Dict<WrapperStr> _map_includes;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif
