#ifndef _FLOWBEHAVIOR_H
#define _FLOWBEHAVIOR_H




class FlowBehavior
{
public:
    QByteArray weight;

    QByteArray guard;

    QByteArray selection;

    QByteArray transformation;

    void read();

    void unload();

};

#endif
