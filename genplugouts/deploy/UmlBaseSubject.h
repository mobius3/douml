#ifndef _UMLBASESUBJECT_H
#define _UMLBASESUBJECT_H


#include <q3cstring.h>
#include <q3ptrvector.h>

class UmlSubject;

// this class manages subjects
class UmlBaseSubject
{
public:
    // return the name
    const Q3CString & name() const {
        return _name;
    }


private:
    Q3CString _name;

    int _x;

    int _y;

    int _w;

    int _h;

    // internal, don't call it
    void read_();


public:
    // internal
    static UmlSubject * get_container_(int x, int y, int w, int h, const Q3PtrVector<UmlSubject> & subjects);

    friend class UmlBaseUseCaseDiagramDefinition;
};

#endif
