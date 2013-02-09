#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"
#include <q3cstring.h>
#include "Language.h"
#include <q3dict.h>

class File;
class UmlItem;
class UmlTypeSpec;
class Artifact;

// This class manages 'classes', notes that the class 'ClassItem'
// is a mother class of the class's children.
//
// You can modify it as you want (except the constructor)
class UmlClass : public UmlBaseClass
{
public:
    UmlClass(void * id, const Q3CString & n) : UmlBaseClass(id, n) {
        cpt[kind()] += 1;
    };

    Language language() const;

    static UmlClass * import(File & f, UmlItem * parent, const Q3CString & knd);

    static bool replaceType(UmlTypeSpec & t, Q3CString & target_id, const Q3CString & ts);


private:
    void importAttributes(File & f);

    void importOperations(File & f);

    void importRelations(File & f);

    void importInstantiate(File & f);

    void importActuals(File & f);

    void importFormals(File & f);

    void importClasses(File & f);

    static void importIdlConstant(UmlItem * parent, const Q3CString & id, const Q3CString & s, const Q3CString & doc, Q3Dict<Q3CString> & prop);

    void cplusplus(Q3Dict<Q3CString> & prop);

    void oracle8(Q3Dict<Q3CString> & prop);

    void corba(Q3Dict<Q3CString> & prop);

    void java(Q3Dict<Q3CString> & prop);

    void assocArtifact(Artifact * c, Q3CString & art_path);


public:
    const Q3CString file() const;

    const Q3CString bodyFile() const;


protected:
    Language lang;

    Q3CString _file;

    Q3CString _body_file;

};

inline Language UmlClass::language() const
{
    return lang;
}

inline const Q3CString UmlClass::file() const
{
    return _file;
}

inline const Q3CString UmlClass::bodyFile() const
{
    return _body_file;
}

#endif
