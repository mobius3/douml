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

    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

    //internal, do NOT use it

    static unsigned multiplicity_column(const Q3CString & mult);

    //internal, do NOT use it

    static Q3CString uml_type(const Q3CString & t, Q3CString UmlBuiltin::* f);

    //internal, do NOT use it

    static Q3CString uml_rel_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    //internal, do NOT use it

    static Q3CString uml_class_stereotype(const Q3CString & t, Q3CString UmlStereotype::* f);

    //internal, do NOT use it

    static UmlBuiltin * add_type(const Q3CString & s);

    //internal, do NOT use it

    static UmlStereotype * add_rel_stereotype(const Q3CString & s);

    //internal, do NOT use it

    static UmlStereotype * add_class_stereotype(const Q3CString & s);

};

#endif
