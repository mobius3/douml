#ifndef _UMLBASEFRAGMENTCOMPARTMENT_H
#define _UMLBASEFRAGMENTCOMPARTMENT_H


// to avoid compiler warning
#include "UmlFragment.h"

#include <q3ptrvector.h>
#include <q3cstring.h>

class UmlFragment;
class UmlBaseFragment;

// this class manages fragments compartments,
// a fragment without separator contains one compartment
class UmlBaseFragmentCompartment
{
public:
    // return the fragment owning the compartment
    UmlFragment * fragment() const {
        return _fragment;
    }

    // the rank of the compartment in the fragment (0..)
    int rank() const {
        return _rank;
    }

    // the texts placed in the compartment
    const Q3PtrVector<char> & texts() const {
        return _texts;
    }

    // return the fragments contained in the compartment,
    // may be none
    const Q3PtrVector<UmlFragment> & contained() const {
        return _contained;
    }

    // return the continuation ('label' case), or an empty string/null
    Q3CString startContinuation() const {
        return _start_continuation;
    }

    // return the continuation ('goto' case), or an empty string/null
    Q3CString endContinuation() const {
        return _end_continuation;
    }


private:
    UmlFragment * _fragment;

    Q3PtrVector<UmlFragment> _contained;

    int _rank;

    Q3PtrVector<char> _texts;

    int _y;

    Q3CString _start_continuation;

    Q3CString _end_continuation;


public:
    void add_contained_(UmlFragment * x);

    void add_text_(Q3CString x);

    //internal, do NOT use it

    void add_cont_(Q3CString s, int cy);

    int b() const {
        return _y;
    }

    bool smaller(const UmlBaseFragmentCompartment * x) const;


private:
    // internal, don't call it
    void read_(UmlBaseFragment * fragment, int rank);


public:
    //  to avoid compiler warning, don't call it
    ~UmlBaseFragmentCompartment();

    friend class UmlBaseFragment;
    friend class UmlBaseUseCaseDiagramDefinition;
    friend class UmlBaseSequenceDiagramDefinition;
};

#endif
