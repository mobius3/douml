#ifndef _ARTIFACT_H
#define _ARTIFACT_H


#include "Language.h"
#include <QByteArray>
#include <QHash>
class File;
class UmlPackage;
class UmlClass;

class Artifact
{
protected:
    Language language;

    QByteArray name;

    QByteArray stereotype;

    QByteArray description;

    QByteArray cpp_path;

    QByteArray java_path;

    QByteArray cpp_namespace;

    QByteArray java_package;

    QByteArray idl_module;

    static QHash<QByteArray,Artifact*> all;


public:
    static Artifact * find(const QByteArray & uid);

    static void import_component_view(File & f);

    static void import_components(File & f);

    static void import(File & f);

    //'pack' is the package containing the class view where 'cl' is defined
    //'cl' is not nested in an other class
    //'art_path' is the rose path of the artifact
    void add(UmlPackage * pack, UmlClass * cl, QByteArray & art_path);

    void add_cpp(UmlPackage * pack, UmlClass * cl, QByteArray h, QByteArray src);

    void add_corba(UmlPackage * pack, UmlClass * cl, QByteArray src);

    void add_java(UmlPackage * pack, UmlClass * cl, QByteArray art_path, QByteArray src);

    QByteArray normalize(QByteArray path, QByteArray root);

};

#endif
