#ifndef _PYTHONSETTINGS_H
#define _PYTHONSETTINGS_H

#ifdef WITHPYTHON


#include <q3cstring.h>
#include "UmlSettings.h"
#include <q3dict.h>

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

    // return the  default indent step
    static const Q3CString & indentStep();

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
    static Q3CString relationAttributeStereotype(const Q3CString & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(Q3CString s, Q3CString v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static Q3CString relationAttributeUmlStereotype(const Q3CString & s);

    // returns the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    static Q3CString classStereotype(const Q3CString & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(Q3CString s, Q3CString v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static Q3CString classUmlStereotype(const Q3CString & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Python type given in argument.
    static Q3CString get_import(const Q3CString & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Python type given in argument.
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

    // returns the extension of the file produced by the PYTHON code generator
    static const Q3CString & sourceExtension();

    // set the extension of the file produced by the PYTHON code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(Q3CString v);

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

    // returns the default definition of an attribute depending on the multiplicity
    static const Q3CString & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, Q3CString v);

    // returns the default definition of an enumeration item
    static Q3CString enumItemDecl();

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

    // returns the default definition of an operation
    static const Q3CString & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(Q3CString v);

    // returns the default definition of __init__
    static const Q3CString & initOperationDef();

    // set the default definition of __init__
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InitOperationDef(Q3CString v);

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


private:
    // never called !
    PythonSettings() {};

    static unsigned mult_column(const Q3CString & mult);

    static bool _defined;

    static bool _2_2;

    static Q3CString _indent_step;

    static Q3CString _root;

    static Q3CString _class_decl;

    static Q3CString _external_class_decl;

    static Q3CString _enum_decl;

    static Q3CString _attr_decl[2/*multiplicity*/];

    static Q3CString _enum_item_decl;

    static Q3CString _rel_decl[2/*relation kind*/][2/*multiplicity*/];

    static Q3CString _oper_def;


protected:
    static Q3CString _initoper_def;


private:
    static Q3CString _get_name;

    static Q3CString _set_name;

    static Q3CString _src_content;

    static Q3CString _ext;

    static Q3Dict<Q3CString> _map_imports;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
