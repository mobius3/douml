#ifndef _CLASSINSTANCE_H
#define _CLASSINSTANCE_H


#include <q3ptrlist.h>

#include <q3valuelist.h>

class FileIn;
class Token;
class UmlItem;

class ClassInstance
{
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

        WrapperStr featureId;

        WrapperStr value;

        WrapperStr valueId;

    };


    Q3ValueList<Slot> bindings;

    WrapperStr id;

    WrapperStr name;

    WrapperStr classifierId;

    UmlItem * where;

};

#endif
