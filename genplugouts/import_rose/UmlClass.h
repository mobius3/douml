#ifndef _UMLCLASS_H
#define _UMLCLASS_H


#include "UmlBaseClass.h"
#include <QByteArray>
#include "Language.h"


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
    UmlClass(void * id, const QByteArray & n) : UmlBaseClass(id, n) {
        cpt[kind()] += 1;
    };

    Language language() const;

    static UmlClass * import(File & f, UmlItem * parent, const QByteArray & knd);

    static bool replaceType(UmlTypeSpec & t, QByteArray & target_id, const QByteArray & ts);


private:
    void importAttributes(File & f);

    void importOperations(File & f);

    void importRelations(File & f);

    void importInstantiate(File & f);

    void importActuals(File & f);

    void importFormals(File & f);

    void importClasses(File & f);

    static void importIdlConstant(UmlItem * parent, const QByteArray & id, const QByteArray & s, const QByteArray & doc, QHash<QByteArray, QByteArray*> & prop);

    void cplusplus(QHash<QByteArray, QByteArray*> & prop);

    void oracle8(QHash<QByteArray, QByteArray*> & prop);

    void corba(QHash<QByteArray, QByteArray*> & prop);

    void java(QHash<QByteArray, QByteArray*> & prop);

    void assocArtifact(Artifact * c, QByteArray & art_path);


public:
    const QByteArray file() const;

    const QByteArray bodyFile() const;


protected:
    Language lang;

    QByteArray _file;

    QByteArray _body_file;

};

inline Language UmlClass::language() const
{
    return lang;
}

inline const QByteArray UmlClass::file() const
{
    return _file;
}

inline const QByteArray UmlClass::bodyFile() const
{
    return _body_file;
}

#endif
