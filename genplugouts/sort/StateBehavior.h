#ifndef _STATEBEHAVIOR_H
#define _STATEBEHAVIOR_H


#include <q3cstring.h>

class StateBehavior
{
public:
    Q3CString on_entry;

    Q3CString on_exit;

    Q3CString do_activity;

    void read();

    void unload();

};

#endif
