#ifndef _ARTIFACT_H
#define _ARTIFACT_H


#include "Language.h"
#include <q3cstring.h>
#include <q3asciidict.h>

class File;
class UmlPackage;
class UmlClass;

class Artifact
{
protected:
    Language language;

    Q3CString name;

    Q3CString stereotype;

    Q3CString description;

    Q3CString cpp_path;

    Q3CString java_path;

    Q3CString cpp_namespace;

    Q3CString java_package;

    Q3CString idl_module;

    static Q3AsciiDict<Artifact> all;


public:
    static Artifact * find(const Q3CString & uid);

    static void import_component_view(File & f);

    static void import_components(File & f);

    static void import(File & f);

    //'pack' is the package containing the class view where 'cl' is defined
    //'cl' is not nested in an other class
    //'art_path' is the rose path of the artifact
    void add(UmlPackage * pack, UmlClass * cl, Q3CString & art_path);

    void add_cpp(UmlPackage * pack, UmlClass * cl, Q3CString h, Q3CString src);

    void add_corba(UmlPackage * pack, UmlClass * cl, Q3CString src);

    void add_java(UmlPackage * pack, UmlClass * cl, Q3CString art_path, Q3CString src);

    Q3CString normalize(Q3CString path, Q3CString root);

};

#endif
