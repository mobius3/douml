#ifndef _CPPSETTINGS_H
#define _CPPSETTINGS_H

#ifdef WITHCPP


#include "misc/mystr.h"
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
    static WrapperStr type(WrapperStr s);

    // set the C++ type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(WrapperStr s, WrapperStr v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the C++ type given in argument
    static WrapperStr umlType(WrapperStr s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr relationAttributeStereotype(WrapperStr s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(WrapperStr s, WrapperStr v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static WrapperStr relationAttributeUmlStereotype(WrapperStr s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr classStereotype(WrapperStr s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(WrapperStr s, WrapperStr v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static WrapperStr classUmlStereotype(WrapperStr s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    static WrapperStr include(WrapperStr s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(WrapperStr s, WrapperStr v);

    // returns the 'root' directory
    static WrapperStr rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(WrapperStr v);

    // returns the default header file content
    static WrapperStr headerContent();

    // set the default header file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderContent(WrapperStr v);

    // returns the default source file content
    static WrapperStr sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(WrapperStr v);

    // returns the extension of the header files produced by the
    // C++ code generator
    static WrapperStr headerExtension();

    // set the extension of the header files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderExtension(WrapperStr v);

    // returns the extension of the source files produced by the
    // C++ code generator
    static WrapperStr sourceExtension();

    // set the extension of the source files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(WrapperStr v);

    // return the regular expression used to bypass
    // dir s on reverse/roundtrip
    static WrapperStr reverseRoundtripDirRegExp();

    // return if the regular expression used to bypass
    // dir s on reverse/roundtrip is case sensitive
    static bool isReverseRoundtripDirRegExpCaseSensitive();

    // set the regular expression used to bypass
    // dir s on reverse/roundtrip
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ReverseRoundtripDirRegExp(WrapperStr s, bool cs);

    // return the regular expression used to bypass
    // file s on reverse/roundtrip
    static WrapperStr reverseRoundtripFileRegExp();

    // return if the regular expression used to bypass
    // file s on reverse/roundtrip is case sensitive
    static bool isReverseRoundtripFileRegExpCaseSensitive();

    // set the regular expression used to bypass
    // file s on reverse/roundtrip
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ReverseRoundtripFileRegExp(WrapperStr s, bool cs);

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

    // return if the fact an operation is inline force the header of the
    // types referenced in the profile to be included in the header
    static bool isInlineOperationForceIncludesInHeader();

    // set if the fact an operation is inline force the header of the
    // types referenced in the profile to be included in the header
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsInlineOperationForceIncludesInHeader(bool v);

    // return if  generate Javadoc style comment
    static bool isGenerateJavadocStyleComment();

    // set if  generate Javadoc style comment
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGenerateJavadocStyleComment(bool v);

    // return the indent of the visibility
    static const WrapperStr & visibilityIndent();

    // set visibility indent
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_VisibilityIndent(WrapperStr v);

    // returns the default operation 'in' parameter specification
    // in case its type is an enum
    static const WrapperStr & enumIn();

    // set the default operation 'in' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumIn(WrapperStr v);

    // returns the default operation 'out' parameter specification
    // in case its type is an enum
    static const WrapperStr & enumOut();

    // set the default operation 'out' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumOut(WrapperStr v);

    // returns the default operation 'inout' parameter specification
    // in case its type is an enum
    static const WrapperStr & enumInout();

    // set the default operation 'inout' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumInout(WrapperStr v);

    // return the default operation value type form
    static WrapperStr enumReturn();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumReturn(WrapperStr v);

    // returns the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static WrapperStr builtinIn(WrapperStr s);

    // set the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinIn(WrapperStr type, WrapperStr form);

    // returns the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static WrapperStr builtinOut(WrapperStr s);

    // set the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinOut(WrapperStr type, WrapperStr form);

    // returns the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static WrapperStr builtinInOut(WrapperStr s);

    // set the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinInOut(WrapperStr type, WrapperStr form);

    // returns the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static WrapperStr builtinReturn(WrapperStr s);

    // set the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinReturn(WrapperStr type, WrapperStr form);

    // returns the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const WrapperStr & in();

    // set the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_In(WrapperStr v);

    // returns the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const WrapperStr & out();

    // set the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Out(WrapperStr v);

    // returns the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const WrapperStr & inout();

    // set the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_Inout(WrapperStr v);

    // return the default operation value type form
    static WrapperStr Return();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Return(WrapperStr v);

    // returns the default definition of a class
    static const WrapperStr & classDecl();

    // set the default definition of a class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDecl(WrapperStr v);

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

    // returns the default definition of a typedef
    static const WrapperStr & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(WrapperStr v);

    // returns the default definition of an attribute depending on the multiplicity
    static const WrapperStr & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an enumeration item
    static const WrapperStr & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(WrapperStr v);

    // returns the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    static const WrapperStr & relationDecl(bool by_value, const char * multiplicity);

    // set the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(bool by_value, const char * multiplicity, const char * v);

    // returns the default declaration of an operation
    static const WrapperStr & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(WrapperStr v);

    // returns the default definition of an operation
    static const WrapperStr & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(WrapperStr v);

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
    static const WrapperStr & getName();

    // set the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(WrapperStr v);

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
    static const WrapperStr & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(WrapperStr v);

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

    static WrapperStr _root;

    static WrapperStr _in;

    static WrapperStr _out;

    static WrapperStr _inout;

    static WrapperStr _return;

    static WrapperStr _enum_in;

    static WrapperStr _enum_out;

    static WrapperStr _enum_inout;

    static WrapperStr _enum_return;

    static WrapperStr _class_decl;

    static WrapperStr _external_class_decl;

    static WrapperStr _struct_decl;

    static WrapperStr _union_decl;

    static WrapperStr _enum_decl;

    static WrapperStr _typedef_decl;

    static WrapperStr _attr_decl[3/*multiplicity*/];

    static WrapperStr _enum_item_decl;

    static WrapperStr _rel_decl[2/*relation kind*/][3/*multiplicity*/];

    static WrapperStr _oper_decl;

    static WrapperStr _oper_def;

    static bool _force_oper_throw;

    static aVisibility _get_visibility;

    static WrapperStr _get_name;

    static bool _is_get_inline;

    static bool _is_get_const;

    static bool _is_get_value_const;

    static aVisibility _set_visibility;

    static WrapperStr _set_name;

    static bool _is_set_inline;

    static bool _is_set_param_const;

    static bool _is_set_param_ref;

    static WrapperStr _h_content;

    static WrapperStr _src_content;

    static WrapperStr _h_ext;

    static WrapperStr _src_ext;

    static WrapperStr _dir_regexp;

    static bool _dir_regexp_case_sensitive;

    static WrapperStr _file_regexp;

    static bool _file_regexp_case_sensitive;

    static bool _incl_with_path;

    static bool _is_relative_path;

    static bool _is_root_relative_path;

    static bool _is_force_namespace_gen;

    static bool _is_generate_javadoc_comment;

    static bool _is_inline_force_header_in_h;

    static WrapperStr _visibility_indent;

    static Q3Dict<QString> _map_includes;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif

