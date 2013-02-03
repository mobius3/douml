#ifndef _STATEBEHAVIOR_H
#define _STATEBEHAVIOR_H


#include "misc/mystr.h"

class StateBehavior
{
public:
    WrapperStr on_entry;

    WrapperStr on_exit;

    WrapperStr do_activity;

    void read();

    void unload();

};

#endif
