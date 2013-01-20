#ifndef SIGNALBLOCKERWRAPPER_H
#define SIGNALBLOCKERWRAPPER_H


#include <stdexcept>
#include <typeinfo>
#include <QObject>
#include <QCoreApplication>

template<class T>
class QSignalBlockerCallProxy
{
    T * const o;
public:
    explicit QSignalBlockerCallProxy( T * oo )
      : o(oo)
    {
    }
    T* operator->()
    {
         return o;
    }
    ~QSignalBlockerCallProxy()
    {
        if(o)
            o->blockSignals(false);
    }
};

template<class T>
class QSignalBlocker
{
    T * const o;
public:
    explicit QSignalBlocker( T * oo )
      : o(oo)
    {
    }
    QSignalBlockerCallProxy<T> operator->()
    {
         if (o)
             o->blockSignals( true );
         return QSignalBlockerCallProxy<T>(o);
    }
    ~QSignalBlocker() {}
};

template<class T>
QSignalBlocker<T> SilentCall(T* o)
{
    return QSignalBlocker<T>(o);
}

#endif // SIGNALBLOCKERWRAPPER_H
