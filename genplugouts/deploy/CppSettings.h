#ifndef _CPPSETTINGS_H
#define _CPPSETTINGS_H

#ifdef WITHCPP


#include <q3cstring.h>
#include "aVisibility.h"
#include "UmlSettings.h"
#include <q3dict.h>

// This class manages settings concerning C++, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'CppSettings::member' rather than
// 'CppSettings::instance()->member' or other long sentence like this.
class CppSettings : public UmlSettings
{
public:
    // returns TRUE when the created C++ objects are initialized
    // with the default declaration/definition
    static bool useDefaults();

    // if y is TRUE the future created C++ objects will be initialized
    // with the default declaration/definition
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UseDefaults(bool y);

    // returns the C++ type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    static Q3CString type(Q3CString s);

    // set the C++ type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(Q3CString s, Q3CString v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the C++ type given in argument
    static Q3CString umlType(Q3CString s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString relationAttributeStereotype(Q3CString s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(Q3CString s, Q3CString v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static Q3CString relationAttributeUmlStereotype(Q3CString s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString classStereotype(Q3CString s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(Q3CString s, Q3CString v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static Q3CString classUmlStereotype(Q3CString s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    static Q3CString include(Q3CString s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(Q3CString s, Q3CString v);

    // returns the 'root' directory
    static Q3CString rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(Q3CString v);

    // returns the default header file content
    static Q3CString headerContent();

    // set the default header file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderContent(Q3CString v);

    // returns the default source file content
    static Q3CString sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(Q3CString v);

    // returns the extension of the header files produced by the
    // C++ code generator
    static Q3CString headerExtension();

    // set the extension of the header files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderExtension(Q3CString v);

    // returns the extension of the source files produced by the
    // C++ code generator
    static Q3CString sourceExtension();

    // set the extension of the source files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(Q3CString v);

    // indicates to the code generator if the #include may specify
    // the path of just the file's name
    static bool includeWithPath();

    // to indicates to the code generator if the #include may specify
    // the path of just the file's name
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IncludeWithPath(bool v);

    // return if a relative path must be used when the path
    // must be generated in the produced #includes
    static bool isRelativePath();

    // set if a relative path must be used when the path
    // must be generated in the produced #includes
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsRelativePath(bool v);

    // return if a path relative to the project root must be used
    // when the path must be generated in the produced #includes
    static bool isRootRelativePath();

    // set if a relative to the project root path must be used
    // when the path must be generated in the produced #includes
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsRootRelativePath(bool v);

    // return if the namespace prefix must be
    // always generated before class's names
    static bool isForceNamespacePrefixGeneration();

    // set if the namespace prefix must be always generated before class's names
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsForceNamespacePrefixGeneration(bool v);

    // return if  generate Javadoc style comment
    static bool isGenerateJavadocStyleComment();

    // set if  generate Javadoc style comment
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGenerateJavadocStyleComment(bool v);

    // returns the default operation 'in' parameter specification
    // in case its type is an enum
    static const Q3CString & enumIn();

    // set the default operation 'in' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumIn(Q3CString v);

    // returns the default operation 'out' parameter specification
    // in case its type is an enum
    static const Q3CString & enumOut();

    // set the default operation 'out' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumOut(Q3CString v);

    // returns the default operation 'inout' parameter specification
    // in case its type is an enum
    static const Q3CString & enumInout();

    // set the default operation 'inout' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumInout(Q3CString v);

    // return the default operation value type form
    static Q3CString enumReturn();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumReturn(Q3CString v);

    // returns the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static Q3CString builtinIn(Q3CString s);

    // set the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinIn(Q3CString type, Q3CString form);

    // returns the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static Q3CString builtinOut(Q3CString s);

    // set the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinOut(Q3CString type, Q3CString form);

    // returns the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static Q3CString builtinInOut(Q3CString s);

    // set the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinInOut(Q3CString type, Q3CString form);

    // returns the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static Q3CString builtinReturn(Q3CString s);

    // set the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinReturn(Q3CString type, Q3CString form);

    // returns the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const Q3CString & in();

    // set the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_In(Q3CString v);

    // returns the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const Q3CString & out();

    // set the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Out(Q3CString v);

    // returns the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const Q3CString & inout();

    // set the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_Inout(Q3CString v);

    // return the default operation value type form
    static Q3CString Return();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Return(Q3CString v);

    // returns the default definition of a class
    static const Q3CString & classDecl();

    // set the default definition of a class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDecl(Q3CString v);

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

    // returns the default definition of a typedef
    static const Q3CString & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(Q3CString v);

    // returns the default definition of an attribute depending on the multiplicity
    static const Q3CString & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of an enumeration item
    static const Q3CString & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(Q3CString v);

    // returns the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    static const Q3CString & relationDecl(bool by_value, const char * multiplicity);

    // set the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(bool by_value, const char * multiplicity, const char * v);

    // returns the default declaration of an operation
    static const Q3CString & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(Q3CString v);

    // returns the default definition of an operation
    static const Q3CString & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(Q3CString v);

    // return TRUE if the operations profile must contain 'throw()'
    // when the operations does not have exception
    static bool operationForceThrow();

    // set if the operations profile must contain 'throw()'
    // when the operations does not have exception
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationForceThrow(bool v);

    // returns the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    static aVisibility getVisibility();

    // set the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetVisibility(aVisibility v);

    // returns the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    static const Q3CString & getName();

    // set the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(Q3CString v);

    // returns if a 'get' operation generated through the attribute
    // and relation 'add get operation' menu is inline by default
    static bool isGetInline();

    // set if a 'get' operation generated through the attribute
    // and relation 'add get operation' menu is inline by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGetInline(bool v);

    // returns if a 'get' operation generated through the attribute
    // and relation 'add get operation' menu is const by default
    static bool isGetConst();

    // set if a 'get' operation generated through the attribute
    // and relation 'add get operation' menu is const by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGetConst(bool v);

    // returns if the value returned by a 'get' operation generated through
    // the attribute and relation 'add get operation' menu is const by default
    static bool isGetValueConst();

    // set if the value returned by a 'get' operation generated through
    // the attribute and relation 'add get operation' menu is const by default
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGetValueConst(bool v);

    // returns the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static aVisibility setVisibility();

    // set the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetVisibility(aVisibility v);

    // returns the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static const Q3CString & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(Q3CString v);

    // returns if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is inline by default
    static bool isSetInline();

    // set if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is inline by default
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetInline(bool v);

    // returns if the parameters of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu are const by default
    static bool isSetParamConst();

    // set if the parameters of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu are const by default
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetParamConst(bool v);

    // return if the parameter of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu is a reference by default
    static bool isSetParamRef();

    // set if the parameter of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu is a reference by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetParamRef(bool v);


private:
    // never called !
    CppSettings() {};

    static bool _defined;

    static Q3CString _root;

    static Q3CString _in;

    static Q3CString _out;

    static Q3CString _inout;

    static Q3CString _return;

    static Q3CString _enum_in;

    static Q3CString _enum_out;

    static Q3CString _enum_inout;

    static Q3CString _enum_return;

    static Q3CString _class_decl;

    static Q3CString _external_class_decl;

    static Q3CString _struct_decl;

    static Q3CString _union_decl;

    static Q3CString _enum_decl;

    static Q3CString _typedef_decl;

    static Q3CString _attr_decl[3/*multiplicity*/];

    static Q3CString _enum_item_decl;

    static Q3CString _rel_decl[2/*relation kind*/][3/*multiplicity*/];

    static Q3CString _oper_decl;

    static Q3CString _oper_def;

    static bool _force_oper_throw;

    static aVisibility _get_visibility;

    static Q3CString _get_name;

    static bool _is_get_inline;

    static bool _is_get_const;

    static bool _is_get_default;
    static bool _is_get_delete;
    static bool _is_get_override;
    static bool _is_get_final;

    static bool _is_get_value_const;

    static aVisibility _set_visibility;

    static Q3CString _set_name;

    static bool _is_set_inline;

    static bool _is_set_param_const;

    static bool _is_set_param_ref;

    static Q3CString _h_content;

    static Q3CString _src_content;

    static Q3CString _h_ext;

    static Q3CString _src_ext;

    static bool _incl_with_path;

    static bool _is_relative_path;

    static bool _is_root_relative_path;

    static bool _is_force_namespace_gen;

    static bool _is_generate_javadoc_comment;

    static Q3Dict<Q3CString> _map_includes;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif

