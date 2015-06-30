#ifndef _UMLITEM_H
#define _UMLITEM_H


#include "UmlBaseItem.h"

#include "aLanguage.h"
#include "aVisibility.h"
#include "aDirection.h"
#include "aParameterEffectKind.h"
#include "anOrdering.h"
#include "Vector.h"
#include "FileWriter.h"

#include <QTextStream.h>
class UmlDiagram;
class UmlTypeSpec;

// This class is a mother class for all the other Uml* classes, this
// allows to generalize their management, declare virtual operations etc ...
//
// You can modify it as you want (except the constructor)
class UmlItem : public UmlBaseItem
{
public:
    UmlItem(void * id, const QByteArray & n) : UmlBaseItem(id, n), known(FALSE) { };

    virtual ~UmlItem();

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //  Set the directory where the files will be generated
    //  initializing 'directory'.
    //
    //  May be remove already existing html files and css

    void set_dir(int argc, char ** argv);

    virtual void memo_ref();

    void define();

    static void start_file(QByteArray f, QByteArray s, bool withrefs);

    static void end_file();

    static void ref_indexes();

    static void generate_indexes();

    static void frame();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level) = 0;

    virtual bool chapterp();

    void html(QByteArray pfix, unsigned int rank, QByteArray what, unsigned int level, QByteArray kind);

    void html(const char * what, UmlDiagram * diagram);

    void write_children(QByteArray pfix, unsigned int rank, unsigned int level);

    void write_dependencies();

    void write_properties();

    void chapter(QByteArray k, QByteArray pfix, unsigned int rank, QByteArray kind, unsigned int level);

    //bypass the comments at the beginning of the form

    const char * bypass_comment(const char * s);

    void manage_alias(const char *& p);

    virtual void write();

    virtual void write(QByteArray target);

    static void writeq(QByteArray s);

    static void writeq(char c);

    static void write(const UmlTypeSpec & t, aLanguage lang);

    static void write(const UmlTypeSpec & t);

    static void write(aVisibility v, aLanguage lang);

    static void write(aVisibility v);

    static void write(aDirection d);

    static void write(aParameterEffectKind d);

    static void write(anOrdering d);

    static void generate_index(Vector & v, QByteArray k, QByteArray r);

    static void sort(Vector & v);


private:
    static void sort(Vector & v, int low, int high);

    bool gt(UmlItem * other);


public:
    virtual QByteArray pretty_name();


protected:
    static Vector all;

    bool known;

    static FileWriter fw;

    static QByteArray directory;

    static unsigned int nrefs;

    static QByteArray letters;

    //true => use SVG picture rather than PNG
    static bool flat;

    //true => classes and tables are generated in index.html, else an own files are generated
    static bool svg;

};

#endif
