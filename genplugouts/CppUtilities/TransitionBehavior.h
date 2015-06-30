#ifndef _TRANSITIONBEHAVIOR_H
#define _TRANSITIONBEHAVIOR_H




class TransitionBehavior
{
public:
    QByteArray trigger;

    QByteArray guard;

    QByteArray activity;

    void read();

    void unload();

};

#endif
