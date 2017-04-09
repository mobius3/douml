#ifndef _PYTHONSETTINGS_H
#define _PYTHONSETTINGS_H

#ifdef WITHPYTHON



#include "UmlSettings.h"


// This class manages settings concerning PYTHON, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'PythonSettings::member' rather than
// 'PythonSettings::instance()->member' or other long sentence like this.
class PythonSettings : public UmlSettings
{
public:
    // return if classes follow Python 2.2 by default
    static bool isPython_2_2();

    // set if classes follow Python 2.2 by default
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsPython_2_2(bool y);

    // returns if operations follow Python 3 (pep-3107)
    static bool isPython_3_operation();

    // set if operations follow Python 3 (pep-3107)
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsPython_3_operation(bool y);

    // return the  default indent step
    static const QByteArray & indentStep();

    // set default indent step
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IndentStep(char * v);

    // returns TRUE when the created Python objects are initialized
    // with the default declaration/definition
    static bool useDefaults();

    // if y is TRUE the future created Python objects will be initialized
    // with the default declaration/definition
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UseDefaults(bool y);

    // returns the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray relationAttributeStereotype(const QByteArray & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(QByteArray s, QByteArray v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static QByteArray relationAttributeUmlStereotype(const QByteArray & s);

    // returns the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    static QByteArray classStereotype(const QByteArray & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(QByteArray s, QByteArray v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static QByteArray classUmlStereotype(const QByteArray & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Python type given in argument.
    static QByteArray get_import(const QByteArray & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Python type given in argument.
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

    // returns the extension of the file produced by the PYTHON code generator
    static const QByteArray & sourceExtension();

    // set the extension of the file produced by the PYTHON code generator
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

    // returns the default definition of an enumeration
    static QByteArray enumDecl();

    // set the default definition of an enumeration
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_EnumDecl(QByteArray v);

    // returns the default definition of an attribute depending on the multiplicity
    static const QByteArray & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, QByteArray v);

    // returns the default definition of an enumeration item
    static QByteArray enumItemDecl();

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

    // returns the default definition of an operation
    static const QByteArray & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(QByteArray v);

    // returns the default definition of __init__
    static const QByteArray & initOperationDef();

    // set the default definition of __init__
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InitOperationDef(QByteArray v);

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


private:
    // never called !
    PythonSettings() {};

    static unsigned mult_column(const QByteArray & mult);

    static bool _defined;

    static bool _2_2;


protected:
    static bool _operation_3;


private:
    static QByteArray _indent_step;

    static QByteArray _root;

    static QByteArray _class_decl;

    static QByteArray _external_class_decl;

    static QByteArray _enum_decl;

    static QByteArray _attr_decl[2/*multiplicity*/];

    static QByteArray _enum_item_decl;

    static QByteArray _rel_decl[2/*relation kind*/][2/*multiplicity*/];

    static QByteArray _oper_def;


protected:
    static QByteArray _initoper_def;


private:
    static QByteArray _get_name;

    static QByteArray _set_name;

    static QByteArray _src_content;

    static QByteArray _ext;

    static QHash<QByteArray,QByteArray*> _map_imports;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
