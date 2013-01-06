#ifndef _FILEOUT_H
#define _FILEOUT_H


#include <q3textstream.h>
#include <qmap.h>
#include <q3cstring.h>

class QFile;
class UmlItem;

//QTextOStream + usefull operations
class FileOut : public Q3TextStream
{
public:
    FileOut(QFile * fp);

    void indent();

    void indent(int dir) {
        _indent += dir;
    }

    void id(const UmlItem * x);

    void idref(const UmlItem * x);

    void idref(Q3CString s, const UmlItem * x);

    void ref(const UmlItem * x);

    void idref_datatype(const Q3CString & t);

    void define_datatypes(int taggedvalue_mode);

    void quote(const char * s);


protected:
    int _indent;

    QMap<Q3CString, int> _datatypes;

    QMap<Q3CString, int> _modifiedtypes;

};

#endif
