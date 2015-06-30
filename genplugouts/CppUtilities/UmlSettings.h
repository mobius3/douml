#ifndef _UMLSETTINGS_H
#define _UMLSETTINGS_H
#include <QByteArray>
#include "aLanguage.h"
#include <QHash>

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
    static QByteArray artifactDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ArtifactDescription(QByteArray v);

    // return the default description
    static QByteArray classDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_ClassDescription(QByteArray v);

    // return the default description
    static QByteArray operationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_OperationDescription(QByteArray v);

    // return the default description
    static QByteArray attributeDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_AttributeDescription(QByteArray v);

    // return the default description
    static QByteArray relationDescription();

    // set the default description
    //
    // On error : return FALSE in C++, produce a RuntimeException in Java
    static bool set_RelationDescription(QByteArray v);

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
    static QByteArray _artifact_default_description;

    static QByteArray _class_default_description;

    static QByteArray _operation_default_description;

    static QByteArray _attribute_default_description;

    static QByteArray _relation_default_description;
    static QHash<QByteArray,UmlStereotype*> _map_relation_attribute_stereotypes;

    static QHash<QByteArray,UmlBuiltin*> _map_builtins;

    static UmlBuiltin * _builtins;

    static QHash<QByteArray,UmlStereotype*> _map_relation_stereotypes;

    static UmlStereotype * _relation_attribute_stereotypes;

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

    static QByteArray uml_rel_attr_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    //internal, do NOT use it

    static QByteArray uml_class_stereotype(const QByteArray & t, QByteArray UmlStereotype::* f);

    //internal, do NOT use it

    static UmlBuiltin * add_type(const QByteArray & s);

    //internal, do NOT use it

    static UmlStereotype * add_rel_attr_stereotype(const QByteArray & s);

    //internal, do NOT use it

    static UmlStereotype * add_class_stereotype(const QByteArray & s);

};

#endif
