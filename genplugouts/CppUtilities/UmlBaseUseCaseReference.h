#ifndef _UMLBASEUSECASEREFERENCE_H
#define _UMLBASEUSECASEREFERENCE_H


#include <q3ptrvector.h>

class UmlUseCase;
class UmlFragmentCompartment;
class UmlSubject;
class UmlFragment;

// this class manages use case references
class UmlBaseUseCaseReference
{
public:
    // return the use case
    UmlUseCase * useCase() const {
        return _use_case;
    }

    // return the fragment compartment containing the
    // use case, or 0/null
    UmlFragmentCompartment * fragment() const {
        return _fragment;
    }

    // return the subject containing the use case, or 0/null
    UmlSubject * subject() const {
        return _subject;
    }


private:
    UmlUseCase * _use_case;

    UmlFragmentCompartment * _fragment;

    UmlSubject * _subject;

    int _x;

    int _y;

    int _w;

    int _h;

    // internal, don't call it
    void read_(const Q3PtrVector<UmlFragment> & fragments, const Q3PtrVector<UmlSubject> & subjects);

    friend class UmlBaseUseCaseDiagramDefinition;
};

#endif
