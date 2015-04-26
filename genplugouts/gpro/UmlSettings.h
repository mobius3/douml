#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H
#include <QHash>


#include <QByteArray>

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

    static void read_();

    static void read_if_needed_();

    static unsigned multiplicity_column(const QByteArray & mult);

    static QByteArray uml_type(const QByteArray & t, QByteArray UmlBuiltin::* f);

    static QByteArray uml_rel_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    static QByteArray uml_class_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    static UmlBuiltin * add_type(const QByteArray & s);

    static UmlStereotype * add_rel_stereotype(const QByteArray & s);

    static UmlStereotype * add_class_stereotype(const QByteArray & s);

};

#endif
