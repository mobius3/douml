#ifndef _JAVASETTINGS_H
#define _JAVASETTINGS_H

#ifdef WITHJAVA


#include "misc/mystr.h"
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
    static WrapperStr type(const WrapperStr & s);

    // set the JAVA type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(WrapperStr s, WrapperStr v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the JAVA type given in argument
    static WrapperStr umlType(const WrapperStr & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr relationAttributeStereotype(const WrapperStr & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(WrapperStr s, WrapperStr v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static WrapperStr relationAttributeUmlStereotype(const WrapperStr & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr classStereotype(const WrapperStr & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(WrapperStr s, WrapperStr v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static WrapperStr classUmlStereotype(const WrapperStr & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Java type given in argument.
    static WrapperStr get_import(const WrapperStr & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Java type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Import(WrapperStr s, WrapperStr v);

    //  return the 'root' directory
    static const WrapperStr & rootDir();

    //  set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(WrapperStr v);

    // returns the default source file content
    static const WrapperStr & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(WrapperStr v);

    // returns the extension of the file produced by the JAVA code generator
    static const WrapperStr & sourceExtension();

    // set the extension of the file produced by the JAVA code generator
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

    // returns the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    static const WrapperStr & enumPatternDecl();

    // set the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternDecl(WrapperStr v);

    // returns the default definition of an enumeration
    static WrapperStr enumDecl();

    // set the default definition of an enumeration
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(WrapperStr v);

    // returns the default definition of an interface
    static const WrapperStr & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(WrapperStr v);

    // returns the default definition of an attribute depending on the multiplicity
    static const WrapperStr & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an enumeration item
    static const WrapperStr & enumPatternItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternItemDecl(WrapperStr v);

    //Returns the 'case' form produced in the fromInt operation
    //for each enumeration item

    static const WrapperStr & enumPatternItemCase();

    //  set the 'case' form produced in the fromInt operation
    //  for each enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_EnumPatternItemCase(WrapperStr v);

    // returns the default definition of an enumeration item
    static WrapperStr enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(WrapperStr v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const WrapperStr & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an operation
    static const WrapperStr & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(WrapperStr v);

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
    static const WrapperStr & getName();

    // set the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
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

    static WrapperStr _root;

    static WrapperStr _class_decl;

    static WrapperStr _external_class_decl;

    static WrapperStr _enum_pattern_decl;

    static WrapperStr _enum_decl;

    static WrapperStr _interface_decl;

    static WrapperStr _attr_decl[3/*multiplicity*/];

    static WrapperStr _enum_pattern_item_decl;

    static WrapperStr _enum_pattern_item_case;

    static WrapperStr _enum_item_decl;

    static WrapperStr _rel_decl[3/*multiplicity*/];

    static WrapperStr _oper_def;

    static aVisibility _get_visibility;

    static WrapperStr _get_name;

    static bool _is_get_final;

    static aVisibility _set_visibility;

    static WrapperStr _set_name;

    static bool _is_set_final;

    static bool _is_set_param_final;

    static WrapperStr _src_content;

    static WrapperStr _ext;

    static WrapperStr _dir_regexp;

    static bool _dir_regexp_case_sensitive;

    static WrapperStr _file_regexp;

    static bool _file_regexp_case_sensitive;

    static bool _is_generate_javadoc_comment;

    static bool _is_force_package_gen;

    static Q3Dict<QString> _map_imports;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
