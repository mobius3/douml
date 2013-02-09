#ifndef _UMLBASEUSECASEDIAGRAMDEFINITION_H
#define _UMLBASEUSECASEDIAGRAMDEFINITION_H


// to avoid compiler warning
#include "UmlClass.h"
#include "UmlSubject.h"
#include "UmlFragment.h"
#include "UmlFragmentCompartment.h"
#include "UmlUseCaseReference.h"
#include "UmlUseCaseAssociation.h"

#include <q3ptrvector.h>

class UmlUseCaseReference;
class UmlClass;
class UmlUseCaseAssociation;
class UmlFragment;
class UmlSubject;

// this class manages use case diagram definition
class UmlBaseUseCaseDiagramDefinition
{
public:
    // return the use cases present in the diagram
    const Q3PtrVector<UmlUseCaseReference> & useCases() const {
        return _use_cases;
    }

    // return the actors present in the diagram
    const Q3PtrVector<UmlClass> & actors() const {
        return _actors;
    }

    // return the associations between actor and use case present in the diagram
    const Q3PtrVector<UmlUseCaseAssociation> & associations() const {
        return _rels;
    }

    // return the fragments present in the diagram
    const Q3PtrVector<UmlFragment> & fragments() const {
        return _fragments;
    }

    // return the subjects present in the diagram
    const Q3PtrVector<UmlSubject> & subjects() const {
        return _subjects;
    }


private:
    Q3PtrVector<UmlUseCaseReference> _use_cases;

    Q3PtrVector<UmlClass> _actors;

    Q3PtrVector<UmlUseCaseAssociation> _rels;

    Q3PtrVector<UmlFragment> _fragments;

    Q3PtrVector<UmlSubject> _subjects;

    // internal, don't call it
    void read_();


public:
    //  to avoid compiler warning, don't call it
    ~UmlBaseUseCaseDiagramDefinition();

    friend class UmlBaseUseCaseDiagram;
};

#endif
