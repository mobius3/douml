#ifndef _TRIGGER_H
#define _TRIGGER_H


#include <q3cstring.h>
#include <qmap.h>

class FileIn;
class Token;
class UmlItem;

class Trigger {
  public:
    static void init();

    //import the trigger starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //the result is null if not find
    
    static Q3CString get(Q3CString idref);

    static void add(FileIn & in, Token & token, Q3CString & name, Q3CString & idref);


  protected:
    static QMap<Q3CString, Q3CString> All;

};

#endif
