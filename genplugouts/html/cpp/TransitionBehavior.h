#ifndef _TRANSITIONBEHAVIOR_H
#define _TRANSITIONBEHAVIOR_H


#include <q3cstring.h>

class TransitionBehavior
{
public:
    Q3CString trigger;

    Q3CString guard;

    Q3CString activity;

    void read();

    void unload();

};

#endif
