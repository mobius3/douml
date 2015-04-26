#ifndef _JAVASETTINGS_H
#define _JAVASETTINGS_H

#ifdef WITHJAVA


#include <QByteArray>
#include "aVisibility.h"
#include "UmlSettings.h"


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
    static QByteArray type(const QByteArray & s);

    // set the JAVA type corresponding to the 'UML' type given in
    // argument, as it is configured in the first 'Generation settings'
    // dialog's tab
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Type(QByteArray s, QByteArray v);

    // reverse of the Type() operation, returns the 'UML' type corresponding
    // to the JAVA type given in argument
    static QByteArray umlType(const QByteArray & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray relationStereotype(const QByteArray & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationStereotype(QByteArray s, QByteArray v);

    // reverse of the RelationStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static QByteArray relationUmlStereotype(const QByteArray & s);

    // returns the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray classStereotype(const QByteArray & s);

    // set the JAVA stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(QByteArray s, QByteArray v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the JAVA one given in argument
    static QByteArray classUmlStereotype(const QByteArray & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Java type given in argument.
    static QByteArray get_import(const QByteArray & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Java type given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_Import(QByteArray s, QByteArray v);

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

    // returns the extension of the file produced by the JAVA code generator
    static const QByteArray & sourceExtension();

    // set the extension of the file produced by the JAVA code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(QByteArray v);

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

    // returns the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    static const QByteArray & enumPatternDecl();

    // set the default definition of an enumeration implemented
    // through an abstract class having constant attributes
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternDecl(QByteArray v);

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
    static const QByteArray & enumPatternItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumPatternItemDecl(QByteArray v);

    //Returns the 'case' form produced in the fromInt operation
    //for each enumeration item

    static const QByteArray & enumPatternItemCase();

    //  set the 'case' form produced in the fromInt operation
    //  for each enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java

    static bool set_EnumPatternItemCase(QByteArray v);

    // returns the default definition of an enumeration item
    static QByteArray enumItemDecl();

    // set the default definition of an enumeration item
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumItemDecl(QByteArray v);

    // returns the default definition of a relation depending on the
    // multiplicity given in argument.
    static const QByteArray & relationDecl(const char * multiplicity);

    // set the default definition of a relation depending on the
    // multiplicity given in argument.
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an operation
    static const QByteArray & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(QByteArray v);

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

    static QByteArray _root;

    static QByteArray _class_decl;

    static QByteArray _external_class_decl;

    static QByteArray _enum_pattern_decl;

    static QByteArray _enum_decl;

    static QByteArray _interface_decl;

    static QByteArray _attr_decl;

    static QByteArray _enum_pattern_item_decl;

    static QByteArray _enum_pattern_item_case;

    static QByteArray _enum_item_decl;

    static QByteArray _rel_decl[3/*multiplicity*/];

    static QByteArray _oper_def;

    static aVisibility _get_visibility;

    static QByteArray _get_name;

    static bool _is_get_final;

    static aVisibility _set_visibility;

    static QByteArray _set_name;

    static bool _is_set_final;

    static bool _is_set_param_final;

    static QByteArray _src_content;

    static QByteArray _ext;

    static QHash<QByteArray,QByteArray*> _map_imports;


protected:
    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

};


#endif

#endif
