#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H


#include <q3cstring.h>
#include "aLanguage.h"
#include <q3dict.h>

struct UmlBuiltin;
struct UmlStereotype;

// This class manages settings not linked with a language, configured through
// the 'Generation settings' dialog.
//
// This class may be defined as a 'singleton', but I prefer to use static
// members allowing to just write 'UmlSettings::member' rather than
// 'UmlSettings::instance()->member' or other long sentence like this.

class UmlSettings
{
public:
    // return the default description
    static Q3CString artifactDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ArtifactDescription(Q3CString v);

    // return the default description
    static Q3CString classDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDescription(Q3CString v);

    // return the default description
    static Q3CString operationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDescription(Q3CString v);

    // return the default description
    static Q3CString attributeDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDescription(Q3CString v);

    // return the default description
    static Q3CString relationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDescription(Q3CString v);

    // return the language from which the getter's name rule must be followed at Uml level
    static aLanguage umlGetName();

    // set the language from which the getter's name rule must be followed at Uml level
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UmlGetName(aLanguage v);

    // return the language from which the setter's name rule must be followed at Uml level
    static aLanguage umlSetName();

    // set the language from which the setter's name rule must be followed at Uml level
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_UmlSetName(aLanguage v);


protected:
    // never called !
    UmlSettings() {};

    static bool _defined;


private:
    static aLanguage _uml_get_name;

    static aLanguage _uml_set_name;


protected:
    static Q3CString _artifact_default_description;

    static Q3CString _class_default_description;

    static Q3CString _operation_default_description;

    static Q3CString _attribute_default_description;

    static Q3CString _relation_default_description;

    static Q3Dict<UmlBuiltin> _map_builtins;

    static UmlBuiltin * _builtins;

    static Q3Dict<UmlStereotype> _map_relation_attribute_stereotypes;

    static UmlStereotype * _relation_attribute_stereotypes;

    static Q3Dict<UmlStereotype> _map_class_stereotypes;

    static UmlStereotype * _class_stereotypes;

    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

    //internal, do NOT use it

    static unsigned multiplicity_column(const Q3CString & mult);

    //internal, do NOT use it

    static Q3CString uml_type(const Q3CString & t, Q3CString UmlBuiltin::* f);

    //internal, do NOT use it

    static Q3CString uml_rel_attr_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    //internal, do NOT use it

    static Q3CString uml_class_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    //internal, do NOT use it

    static UmlBuiltin * add_type(const Q3CString & s);

    //internal, do NOT use it

    static UmlStereotype * add_rel_attr_stereotype(const Q3CString & s);

    //internal, do NOT use it

    static UmlStereotype * add_class_stereotype(const Q3CString & s);

};

#endif
