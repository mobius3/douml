#ifndef _PHPSETTINGS_H
#define _PHPSETTINGS_H

#ifdef WITHPHP



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
    static QByteArray classStereotype(const QByteArray & s);

    // set the PHP stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(QByteArray s, QByteArray v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PHP one given in argument
    static QByteArray classUmlStereotype(const QByteArray & s);

    //  return the 'root' directory
    static const QByteArray & rootDir();

    //  set the 'root' directory
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RootDir(QByteArray v);

    // returns the default source file content
    static const QByteArray & sourceContent();

    // set the default source file content
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceContent(QByteArray v);

    // returns the extension of the file produced by the PHP code generator
    static const QByteArray & sourceExtension();

    // set the extension of the file produced by the PHP code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(QByteArray v);

    // return if  generate Javadoc style comment
    static bool isGenerateJavadocStyleComment();

    // set if  generate Javadoc style comment
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGenerateJavadocStyleComment(bool v);

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

    // returns the default definition of an enumeration
    static QByteArray enumDecl();

    // set the default definition of an enumeration
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(QByteArray v);

    // returns the default definition of an interface
    static const QByteArray & interfaceDecl();

    // set the default definition of an interface
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InterfaceDecl(QByteArray v);

    // returns the default definition of an attribute
    static const QByteArray & attributeDecl();

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(QByteArray v);

    // returns the default definition of an enumeration item
    static QByteArray enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(QByteArray v);

    // returns the default definition of an relation
    static const QByteArray & relationDecl();

    // set the default definition of an relation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(QByteArray v);

    // returns the default definition of an operation
    static const QByteArray & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(QByteArray v);

    // returns the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
    //
    // note : visibility shared with Java
    static aVisibility getVisibility();

    // set the default visibility of a 'get' operation generated
    // through the attribute and relation 'add get operation'
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    //
    // note : visibility shared with Java
    static bool set_GetVisibility(aVisibility v);

    // returns the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
    static const QByteArray & getName();

    // set the default name of a 'get' operation generated
    // through the attribute and relation 'add get operation' menu
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
    //
    //   note : visibility shared with Java
    static aVisibility setVisibility();

    // set the default visibility of a 'set' operation generated
    // through the attribute and relation 'add set operation'
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    //
    //   note : visibility shared with Java
    static bool set_SetVisibility(aVisibility v);


private:
    // never called !
    PhpSettings() {};

    static bool _defined;

    static QByteArray _root;

    static QByteArray _class_decl;

    static QByteArray _external_class_decl;

    static QByteArray _enum_decl;

    static QByteArray _interface_decl;

    static QByteArray _attr_decl;

    static QByteArray _enum_item_decl;

    static QByteArray _rel_decl;

    static QByteArray _oper_def;

#ifndef WITHJAVA
    static aVisibility _get_visibility;
#endif

    static QByteArray _get_name;

    static bool _is_get_final;

#ifndef WITHJAVA
    static aVisibility _set_visibility;
#endif

    static QByteArray _set_name;

    static bool _is_set_final;

    static QByteArray _src_content;

    static QByteArray _ext;

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
