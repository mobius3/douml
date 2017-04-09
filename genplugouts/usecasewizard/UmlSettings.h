#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H
#include <QByteArray>
#include <QHash>



struct UmlBuiltin;
struct UmlStereotype;

//  Do NOT use it, refer to CppSettings, JavaSettings and IdlSettings classes

class UmlSettings
{
protected:
    // never called !
    UmlSettings() {};

    static bool _defined;

    static QHash<QByteArray,UmlBuiltin*> _map_builtins;

    static UmlBuiltin * _builtins;

    static QHash<QByteArray,UmlStereotype*> _map_relation_stereotypes;

    static UmlStereotype * _relation_stereotypes;

    static QHash<QByteArray,UmlStereotype*> _map_class_stereotypes;

    static UmlStereotype * _class_stereotypes;

    //internal, do NOT use it

    static void read_();

    //internal, do NOT use it

    static void read_if_needed_();

    //internal, do NOT use it

    static unsigned multiplicity_column(const QByteArray & mult);

    //internal, do NOT use it

    static QByteArray uml_type(const QByteArray & t, QByteArray UmlBuiltin::* f);

    //internal, do NOT use it

    static QByteArray uml_rel_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    //internal, do NOT use it

    static QByteArray uml_class_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    //internal, do NOT use it

    static UmlBuiltin * add_type(const QByteArray & s);

    //internal, do NOT use it

    static UmlStereotype * add_rel_stereotype(const QByteArray & s);

    //internal, do NOT use it

    static UmlStereotype * add_class_stereotype(const QByteArray & s);

};

#endif
