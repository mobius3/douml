#ifndef _SGNL_H
#define _SGNL_H


#include <q3cstring.h>
#include <qmap.h>

class FileIn;
class Token;
class UmlItem;

class Signal {
  public:
    static void init();

    //import the signal starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //the result is null if not find
    
    static Q3CString get(Q3CString idref);

    static void add(FileIn & in, Token & token, Q3CString & name, Q3CString & idref);


  protected:
    static QMap<Q3CString, Q3CString> All;

};

#endif
