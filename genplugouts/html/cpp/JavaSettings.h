#ifndef _JAVASETTINGS_H
#define _JAVASETTINGS_H

#ifdef WITHJAVA


#include <q3cstring.h>
#include "aVisibility.h"
#include "UmlSettings.h"
#include <q3dict.h>

// This class manages settings concerning JAVA, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'JavaSettings::member' rather than
// 'JavaSettings::instance()->member' or other long sentence like this.
class JavaSettings : public UmlSettings
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

    // returns the JAVA type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    static Q3CString type(const Q3CString & s);

    // set the JAVA type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(Q3CString s, Q3CString v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the JAVA type given in argument
    static Q3CString umlType(const Q3CString & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString relationAttributeStereotype(const Q3CString & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(Q3CString s, Q3CString v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static Q3CString relationAttributeUmlStereotype(const Q3CString & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString classStereotype(const Q3CString & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(Q3CString s, Q3CString v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static Q3CString classUmlStereotype(const Q3CString & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Java type given in argument.
    static Q3CString get_import(const Q3CString & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Java type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Import(Q3CString s, Q3CString v);

    //  return the 'root' directory
    static const Q3CString & rootDir();

    //  set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(Q3CString v);

    // returns the default source file content
    static const Q3CString & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(Q3CString v);

    // returns the extension of the file produced by the JAVA code generator
    static const Q3CString & sourceExtension();

    // set the extension of the file produced by the JAVA code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(Q3CString v);

    // return the regular expression used to bypass
    // dir s on reverse/roundtrip
    static Q3CString reverseRoundtripDirRegExp();

    // return if the regular expression used to bypass
    // dir s on reverse/roundtrip is case sensitive
    static bool isReverseRoundtripDirRegExpCaseSensitive();

    // set the regular expression used to bypass
    // dir s on reverse/roundtrip
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ReverseRoundtripDirRegExp(Q3CString s, bool cs);

    // return the regular expression used to bypass
    // file s on reverse/roundtrip
    static Q3CString reverseRoundtripFileRegExp();

    // return if the regular expression used to bypass
    // file s on reverse/roundtrip is case sensitive
    static bool isReverseRoundtripFileRegExpCaseSensitive();

    // set the regular expression used to bypass
    // file s on reverse/roundtrip
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ReverseRoundtripFileRegExp(Q3CString s, bool cs);

    // return if  generate Javadoc style comment
    static bool isGenerateJavadocStyleComment();

    // set if  generate Javadoc style comment
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGenerateJavadocStyleComment(bool v);

    // return if the package prefix must be
    // always generated before class's names

    static bool isForcePackagePrefixGeneration();

    // set if the package prefix must be always generated before class's names
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_IsForcePackagePrefixGeneration(bool v);

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

    // returns the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    static const Q3CString & enumPatternDecl();

    // set the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternDecl(Q3CString v);

    // returns the default definition of an enumeration
    static Q3CString enumDecl();

    // set the default definition of an enumeration
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(Q3CString v);

    // returns the default definition of an interface
    static const Q3CString & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(Q3CString v);

    // returns the default definition of an attribute depending on the multiplicity
    static const Q3CString & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of an enumeration item
    static const Q3CString & enumPatternItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternItemDecl(Q3CString v);

    //Returns the 'case' form produced in the fromInt operation
    //for each enumeration item

    static const Q3CString & enumPatternItemCase();

    //  set the 'case' form produced in the fromInt operation
    //  for each enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_EnumPatternItemCase(Q3CString v);

    // returns the default definition of an enumeration item
    static Q3CString enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(Q3CString v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const Q3CString & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of an operation
    static const Q3CString & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(Q3CString v);

    // returns the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
    static aVisibility getVisibility();

    // set the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
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

    // returns the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    static const Q3CString & setName();

    // set the default name of a 'set' operation generated
    // through the attribute and relation 'add set operation' menu
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetName(Q3CString v);

    //  return if a 'get' operation generated through the attribute
    //  and relation 'add get operation' menu is final by default
    static bool isGetFinal();

    //  set if a 'get' operation generated through the attribute
    //  and relation 'add get operation' menu is final by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGetFinal(bool v);

    // returns if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is final by default
    static bool isSetFinal();

    // set if a 'set' operation generated through the attribute
    // and relation 'add set operation' menu is final by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetFinal(bool v);

    // returns the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation'
    static aVisibility setVisibility();

    // set the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation'
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetVisibility(aVisibility v);

    // returns if the parameters of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu are final by default
    static bool isSetParamFinal();

    // set if the parameters of a 'set' operation generated through the
    // attribute and relation 'add set operation' menu are final by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsSetParamFinal(bool v);


private:
    // never called !
    JavaSettings() {};

    static bool _defined;

    static Q3CString _root;

    static Q3CString _class_decl;

    static Q3CString _external_class_decl;

    static Q3CString _enum_pattern_decl;

    static Q3CString _enum_decl;

    static Q3CString _interface_decl;

    static Q3CString _attr_decl[3/*multiplicity*/];

    static Q3CString _enum_pattern_item_decl;

    static Q3CString _enum_pattern_item_case;

    static Q3CString _enum_item_decl;

    static Q3CString _rel_decl[3/*multiplicity*/];

    static Q3CString _oper_def;

    static aVisibility _get_visibility;

    static Q3CString _get_name;

    static bool _is_get_final;

    static aVisibility _set_visibility;

    static Q3CString _set_name;

    static bool _is_set_final;

    static bool _is_set_param_final;

    static Q3CString _src_content;

    static Q3CString _ext;

    static Q3CString _dir_regexp;

    static bool _dir_regexp_case_sensitive;

    static Q3CString _file_regexp;

    static bool _file_regexp_case_sensitive;

    static bool _is_generate_javadoc_comment;

    static bool _is_force_package_gen;

    static Q3Dict<Q3CString> _map_imports;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
