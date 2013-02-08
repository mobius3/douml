#ifndef _PHPSETTINGS_H
#define _PHPSETTINGS_H

#ifdef WITHPHP


#include <q3cstring.h>
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
    static Q3CString classStereotype(const Q3CString & s);

    // set the PHP stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(Q3CString s, Q3CString v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PHP one given in argument
    static Q3CString classUmlStereotype(const Q3CString & s);

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

    // returns the extension of the file produced by the PHP code generator
    static const Q3CString & sourceExtension();

    // set the extension of the file produced by the PHP code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(Q3CString v);

    // return if  generate Javadoc style comment
    static bool isGenerateJavadocStyleComment();

    // set if  generate Javadoc style comment
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsGenerateJavadocStyleComment(bool v);

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

    // returns the default definition of an attribute
    static const Q3CString & attributeDecl();

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(Q3CString v);

    // returns the default definition of an enumeration item
    static Q3CString enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(Q3CString v);

    // returns the default definition of an relation
    static const Q3CString & relationDecl();

    // set the default definition of an relation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(Q3CString v);

    // returns the default definition of an operation
    static const Q3CString & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(Q3CString v);

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

    static Q3CString _root;

    static Q3CString _class_decl;

    static Q3CString _external_class_decl;

    static Q3CString _enum_decl;

    static Q3CString _interface_decl;

    static Q3CString _attr_decl;

    static Q3CString _enum_item_decl;

    static Q3CString _rel_decl;

    static Q3CString _oper_def;

#ifndef WITHJAVA
    static aVisibility _get_visibility;
#endif

    static Q3CString _get_name;

    static bool _is_get_final;

#ifndef WITHJAVA
    static aVisibility _set_visibility;
#endif

    static Q3CString _set_name;

    static bool _is_set_final;

    static Q3CString _src_content;

    static Q3CString _ext;

    static bool _is_generate_javadoc_comment;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
