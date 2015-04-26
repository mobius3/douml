#ifndef _CPPSETTINGS_H
#define _CPPSETTINGS_H

#ifdef WITHCPP



#include "aVisibility.h"
#include "UmlSettings.h"


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
    static QByteArray type(QByteArray s);

    // set the C++ type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(QByteArray s, QByteArray v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the C++ type given in argument
    static QByteArray umlType(QByteArray s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray relationAttributeStereotype(QByteArray s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(QByteArray s, QByteArray v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static QByteArray relationAttributeUmlStereotype(QByteArray s);

    // returns the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray classStereotype(QByteArray s);

    // set the C++ stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(QByteArray s, QByteArray v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the C++ one given in argument
    static QByteArray classUmlStereotype(QByteArray s);

    // returns the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    static QByteArray include(QByteArray s);

    // set the #include or other form specified in the last
    // 'Generation settings' tab for the C++ type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Include(QByteArray s, QByteArray v);

    // returns the 'root' directory
    static QByteArray rootDir();

    // set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(QByteArray v);

    // returns the default header file content
    static QByteArray headerContent();

    // set the default header file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderContent(QByteArray v);

    // returns the default source file content
    static QByteArray sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(QByteArray v);

    // returns the extension of the header files produced by the
    // C++ code generator
    static QByteArray headerExtension();

    // set the extension of the header files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_HeaderExtension(QByteArray v);

    // returns the extension of the source files produced by the
    // C++ code generator
    static QByteArray sourceExtension();

    // set the extension of the source files produced by the
    // C++ code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(QByteArray v);

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
    static const QByteArray & enumIn();

    // set the default operation 'in' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumIn(QByteArray v);

    // returns the default operation 'out' parameter specification
    // in case its type is an enum
    static const QByteArray & enumOut();

    // set the default operation 'out' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumOut(QByteArray v);

    // returns the default operation 'inout' parameter specification
    // in case its type is an enum
    static const QByteArray & enumInout();

    // set the default operation 'inout' parameter specification
    // in case its type is an enum
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumInout(QByteArray v);

    // return the default operation value type form
    static QByteArray enumReturn();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumReturn(QByteArray v);

    // returns the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static QByteArray builtinIn(QByteArray s);

    // set the default operation 'in' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinIn(QByteArray type, QByteArray form);

    // returns the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static QByteArray builtinOut(QByteArray s);

    // set the default operation 'out' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinOut(QByteArray type, QByteArray form);

    // returns the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static QByteArray builtinInOut(QByteArray s);

    // set the default operation 'inout' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinInOut(QByteArray type, QByteArray form);

    // returns the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab, else an empty string/null

    static QByteArray builtinReturn(QByteArray s);

    // set the default operation 'return' parameter specification
    // in case its type is specified in the first 'Generation
    // settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_BuiltinReturn(QByteArray type, QByteArray form);

    // returns the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const QByteArray & in();

    // set the default operation 'in' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_In(QByteArray v);

    // returns the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const QByteArray & out();

    // set the default operation 'out' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Out(QByteArray v);

    // returns the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    static const QByteArray & inout();

    // set the default operation 'inout' parameter specification
    // in case its type is not an enum or a type specified in the
    // first 'Generation settings' tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_Inout(QByteArray v);

    // return the default operation value type form
    static QByteArray Return();

    // set the default operation value type form
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Return(QByteArray v);

    // returns the default definition of a class
    static const QByteArray & classDecl();

    // set the default definition of a class
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDecl(QByteArray v);

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

    // returns the default definition of a typedef
    static const QByteArray & typedefDecl();

    // set the default definition of a typedef
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_TypedefDecl(QByteArray v);

    // returns the default definition of an attribute depending on the multiplicity
    static const QByteArray & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an enumeration item
    static const QByteArray & enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(QByteArray v);

    // returns the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    static const QByteArray & relationDecl(bool by_value, const char * multiplicity);

    // set the default definition of a relation depending on it is an
    // aggregation by value or not and the multiplicity, given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(bool by_value, const char * multiplicity, const char * v);

    // returns the default declaration of an operation
    static const QByteArray & operationDecl();

    // set the default declaration of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDecl(QByteArray v);

    // returns the default definition of an operation
    static const QByteArray & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(QByteArray v);

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
    static const QByteArray & getName();

    // set the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_GetName(QByteArray v);

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
    static const QByteArray & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(QByteArray v);

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

    static QByteArray _root;

    static QByteArray _in;

    static QByteArray _out;

    static QByteArray _inout;

    static QByteArray _return;

    static QByteArray _enum_in;

    static QByteArray _enum_out;

    static QByteArray _enum_inout;

    static QByteArray _enum_return;

    static QByteArray _class_decl;

    static QByteArray _external_class_decl;

    static QByteArray _struct_decl;

    static QByteArray _union_decl;

    static QByteArray _enum_decl;

    static QByteArray _typedef_decl;

    static QByteArray _attr_decl[3/*multiplicity*/];

    static QByteArray _enum_item_decl;

    static QByteArray _rel_decl[2/*relation kind*/][3/*multiplicity*/];

    static QByteArray _oper_decl;

    static QByteArray _oper_def;

    static bool _force_oper_throw;

    static aVisibility _get_visibility;

    static QByteArray _get_name;

    static bool _is_get_inline;

    static bool _is_get_const;

    static bool _is_get_value_const;

    static aVisibility _set_visibility;

    static QByteArray _set_name;

    static bool _is_set_inline;

    static bool _is_set_param_const;

    static bool _is_set_param_ref;

    static QByteArray _h_content;

    static QByteArray _src_content;

    static QByteArray _h_ext;

    static QByteArray _src_ext;

    static bool _incl_with_path;

    static bool _is_relative_path;

    static bool _is_root_relative_path;

    static bool _is_force_namespace_gen;

    static bool _is_generate_javadoc_comment;

    static QHash<QByteArray,QByteArray*> _map_includes;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif

