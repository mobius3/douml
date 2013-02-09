#ifndef _PYTHONSETTINGS_H
#define _PYTHONSETTINGS_H

#ifdef WITHPYTHON



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

    // returns if operations follow Python 3 (pep-3107)
    static bool isPython_3_operation();

    // set if operations follow Python 3 (pep-3107)
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_IsPython_3_operation(bool y);

    // return the  default indent step
    static const WrapperStr & indentStep();

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
    static WrapperStr relationAttributeStereotype(const WrapperStr & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationAttributeStereotype(WrapperStr s, WrapperStr v);

    // reverse of the RelationAttributeStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static WrapperStr relationAttributeUmlStereotype(const WrapperStr & s);

    // returns the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    static WrapperStr classStereotype(const WrapperStr & s);

    // set the PYTHON stereotype corresponding to the 'UML' stereotype given
    // in argument
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassStereotype(WrapperStr s, WrapperStr v);

    // reverse of the ClassStereotype() operation, returns the 'UML'
    // stereotype corresponding to the PYTHON one given in argument
    static WrapperStr classUmlStereotype(const WrapperStr & s);

    //returns the import or other form specified in the last
    //'Generation settings' tab for the Python type given in argument.
    static WrapperStr get_import(const WrapperStr & s);

    //  set the import or other form specified in the last
    //  'Generation settings' tab for the Python type given in argument.
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

    // returns the extension of the file produced by the PYTHON code generator
    static const WrapperStr & sourceExtension();

    // set the extension of the file produced by the PYTHON code generator
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_SourceExtension(WrapperStr v);

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

    // returns the default definition of an attribute depending on the multiplicity
    static const WrapperStr & attributeDecl(const char * multiplicity);

    // set the default definition of an attribute
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDecl(const char * multiplicity, WrapperStr v);

    // returns the default definition of an enumeration item
    static WrapperStr enumItemDecl();

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

    // returns the default definition of an operation
    static const WrapperStr & operationDef();

    // set the default definition of an operation
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDef(WrapperStr v);

    // returns the default definition of __init__
    static const WrapperStr & initOperationDef();

    // set the default definition of __init__
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_InitOperationDef(WrapperStr v);

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


private:
    // never called !
    PythonSettings() {};

    static unsigned mult_column(const WrapperStr & mult);

    static bool _defined;

    static bool _2_2;

    static bool _operation_3;

    static WrapperStr _indent_step;

    static WrapperStr _root;

    static WrapperStr _class_decl;

    static WrapperStr _external_class_decl;

    static WrapperStr _enum_decl;

    static WrapperStr _attr_decl[2/*multiplicity*/];

    static WrapperStr _enum_item_decl;

    static WrapperStr _rel_decl[2/*relation kind*/][2/*multiplicity*/];

    static WrapperStr _oper_def;

    static WrapperStr _initoper_def;

    static WrapperStr _get_name;

    static WrapperStr _set_name;

    static WrapperStr _src_content;

    static WrapperStr _ext;

    static Q3Dict<WrapperStr> _map_imports;


protected:
    static void read_();

    static void read_if_needed_();

};


#endif

#endif
