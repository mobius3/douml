#ifndef _FILEOUT_H
#define _FILEOUT_H


#include <q3textstream.h>
#include <qmap.h>
#include <q3cstring.h>

class QFile;
class UmlItem;

//QTextOStream + usefull operations
class FileOut : public Q3TextStream {
  public:
    FileOut(QFile * fp, bool lf, bool utf8);

    void indent();

    void indent(int dir) { _indent += dir; }

    void id(UmlItem * x);

    void id_prefix(UmlItem * x, const char * pfix);

    void id_prefix(UmlItem * x, const char * pfix, int n);

    void idref(UmlItem * x);

    //for C++/Java types
    void idref(Q3CString s, UmlItem * x);

    void idref_prefix(UmlItem * x, const char * pfix);

    void idref_prefix(UmlItem * x, const char * pfix, int n);

    void idref_datatype(const Q3CString & t);

    //output <space><pfix1>="BOUML_<pfix2><x>"
    void ref(UmlItem * x, const char * pfix1, const char * pfix2 = "");

    //output <space><pfix1>="BOUML_<pfix2><n><x>"
    void ref(UmlItem * x, const char * pfix1, const char * pfix2, int n);

    //output BOUML_<pfix><x>
    void ref_only(UmlItem * x, const char * pfix);

    void define_datatypes(bool uml_20, bool primitive_type, bool gen_extension);

    void quote(const Q3CString &s);
    
    void quote(const char * s);

    void quote(char c);


  protected:
    bool _lf;

    int _indent;

    QMap<Q3CString,int> _datatypes;

    QMap<Q3CString,int> _modifiedtypes;

};

#endif
