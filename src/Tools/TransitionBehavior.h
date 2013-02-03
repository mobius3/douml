#ifndef _TRANSITIONBEHAVIOR_H
#define _TRANSITIONBEHAVIOR_H


#include <WrapperStr.h>

class TransitionBehavior
{
public:
    WrapperStr trigger;

    WrapperStr guard;

    WrapperStr activity;

    void read();

    void unload();

};

#endif
