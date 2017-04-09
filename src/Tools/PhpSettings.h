#ifndef _PHPSETTINGS_H
#define _PHPSETTINGS_H

#ifdef WITHPHP


#include "misc/mystr.h"
#include "aVisibility.h"
#include "UmlSettings.h"


// This class manages settings concerning PHP, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'PhpSettings::member' rather than
// 'PhpSettings::instance()->member' or other long sentence like this.
class PhpSettings : public UmlSettings
{
public:
    // returns TRUE when the created Php objects are initialized
    // with the default declaration/definition
    static bool useDefaults();

    // if y is TRUE the future created Php objects will be initialized
    // with the default declaration/definition
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UseDefaults(bool y);

    // returns the PHP stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr classStereotype(const WrapperStr & s);

    // set the PHP stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(WrapperStr s, WrapperStr v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PHP one given in argument
    static WrapperStr classUmlStereotype(const WrapperStr & s);

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

    // returns the extension of the file produced by the PHP code generator
    static const WrapperStr & sourceExtension();

    // set the extension of the file produced by the PHP code generator
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

    // indicates to the code generator if the require_once may specify
    // the path of just the file's name
    static bool requireOnceWithPath();

    // to indicates to the code generator if the require_once may specify
    // the path of just the file's name
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RequireOnceWithPath(bool v);

    // return if a relative path must be used when the path
    // must be generated in the produced require_once
    static bool isRelativePath();

    // set if a relative path must be used when the path
    // must be generated in the produced require_once
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsRelativePath(bool v);

    // return if a path relative to the project root must be used
    // when the path must be generated in the produced require_once
    static bool isRootRelativePath();

    // set if a relative to the project root path must be used
    // when the path must be generated in the produced require_once
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

    // returns the default definition of an attribute
    static const WrapperStr & attributeDecl();

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(WrapperStr v);

    // returns the default definition of an enumeration item
    static WrapperStr enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(WrapperStr v);

    // returns the default definition of a relation
    static const WrapperStr & relationDecl();

    // set the default definition of a relation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(WrapperStr v);

    // returns the default definition of an operation
    static const WrapperStr & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(WrapperStr v);

    // returns the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
    // note : visibility shared with Java
    static aVisibility getVisibility();

    // set the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
    // note : visibility shared with Java
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
    //   note : visibility shared with Java
    static aVisibility setVisibility();

    // set the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation'
    // note : visibility shared with Java
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SetVisibility(aVisibility v);

private:
    // never called !
    PhpSettings() {};

    static bool _defined;

    static WrapperStr _root;

    static WrapperStr _class_decl;

    static WrapperStr _external_class_decl;

    static WrapperStr _enum_decl;

    static WrapperStr _interface_decl;

    static WrapperStr _attr_decl;

    static WrapperStr _enum_item_decl;

    static WrapperStr _rel_decl;

    static WrapperStr _oper_def;

#ifndef WITHJAVA
    static aVisibility _get_visibility;
#endif

    static WrapperStr _get_name;

    static bool _is_get_final;

#ifndef WITHJAVA
    static aVisibility _set_visibility;
#endif

    static WrapperStr _set_name;

    static bool _is_set_final;

    static WrapperStr _src_content;

    static WrapperStr _ext;

    static WrapperStr _dir_regexp;

    static bool _dir_regexp_case_sensitive;

    static WrapperStr _file_regexp;

    static bool _file_regexp_case_sensitive;

    static bool _is_generate_javadoc_comment;

    static bool _req_with_path;

    static bool _is_relative_path;

    static bool _is_root_relative_path;

    static bool _is_force_namespace_gen;

protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
