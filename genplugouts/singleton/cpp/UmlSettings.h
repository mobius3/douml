#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H


#include <q3dict.h>
#include <q3cstring.h>

struct UmlBuiltin;
struct UmlStereotype;

//  Do NOT use it, refer to CppSettings, JavaSettings and IdlSettings classes

class UmlSettings
{
protected:
    // never called !
    UmlSettings() {};

    static bool _defined;

    static Q3Dict<UmlBuiltin> _map_builtins;

    static UmlBuiltin * _builtins;

    static Q3Dict<UmlStereotype> _map_relation_stereotypes;

    static UmlStereotype * _relation_stereotypes;

    static Q3Dict<UmlStereotype> _map_class_stereotypes;

    static UmlStereotype * _class_stereotypes;

    static void read_();

    static void read_if_needed_();

    static unsigned multiplicity_column(const Q3CString & mult);

    static Q3CString uml_type(const Q3CString & t, Q3CString UmlBuiltin::* f);

    static Q3CString uml_rel_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    static Q3CString uml_class_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    static UmlBuiltin * add_type(const Q3CString & s);

    static UmlStereotype * add_rel_stereotype(const Q3CString & s);

    static UmlStereotype * add_class_stereotype(const Q3CString & s);

};

#endif
