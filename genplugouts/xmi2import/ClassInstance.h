#ifndef _CLASSINSTANCE_H
#define _CLASSINSTANCE_H


#include <q3ptrlist.h>
#include <q3cstring.h>
#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class ClassInstance {
  public:
    static void init();

    //import the activity node starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    static void solveThem();


  protected:
    static Q3PtrList<ClassInstance> All;

    struct Slot {
        //import the activity node starting by 'tk' inside 'where'
        void importIt(FileIn & in, Token & token);

        Q3CString featureId;

        Q3CString value;

        Q3CString valueId;

    };
    
    
    Q3ValueList<Slot> bindings;

    Q3CString id;

    Q3CString name;

    Q3CString classifierId;

    UmlItem * where;

};

#endif
