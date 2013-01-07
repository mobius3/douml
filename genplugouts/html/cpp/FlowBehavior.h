#ifndef _FLOWBEHAVIOR_H
#define _FLOWBEHAVIOR_H


#include <q3cstring.h>

class FlowBehavior
{
public:
    Q3CString weight;

    Q3CString guard;

    Q3CString selection;

    Q3CString transformation;

    void read();

    void unload();

};

#endif
