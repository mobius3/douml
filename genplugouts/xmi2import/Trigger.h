#ifndef _TRIGGER_H
#define _TRIGGER_H



#include <qmap.h>

class FileIn;
class Token;
class UmlItem;

class Trigger
{
public:
    static void init();

    //import the trigger starting by 'tk' inside 'where'
    static void importIt(FileIn & in, Token & token, UmlItem * where);

    //the result is null if not find

    static WrapperStr get(WrapperStr idref);

    static void add(FileIn & in, Token & token, WrapperStr & name, WrapperStr & idref);


protected:
    static QMap<QString, WrapperStr> All;

};

#endif
