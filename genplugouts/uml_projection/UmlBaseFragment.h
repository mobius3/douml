#ifndef _UMLBASEFRAGMENT_H
#define _UMLBASEFRAGMENT_H


#include <q3cstring.h>
#include <q3ptrvector.h>
#include <q3ptrdict.h>

class UmlFragmentCompartment;
class UmlDiagram;
class UmlClassInstanceReference;
class UmlFragment;

// this class manages fragments
class UmlBaseFragment
{
public:
    // return the name
    const Q3CString & name() const {
        return _name;
    }

    // return the compartments, at least one compartment exists
    const Q3PtrVector<UmlFragmentCompartment> & compartments() const {
        return _compartments;
    }

    // return the fragment compartment containing the fragment,
    // or 0/null
    UmlFragmentCompartment * container() const {
        return _container;
    }

    // return the diagram optionally referenced by the fragment,
    // generally associated to an interaction use
    UmlDiagram * refer() const {
        return _refer;
    }

    // return the form corresponding to the arguments
    // and return value of the interaction use
    Q3CString arguments() const {
        return _arguments;
    }

    // return the the list of covered instances (life lines)
    const Q3PtrVector<UmlClassInstanceReference> & covered() const {
        return _covered;
    }


private:
    UmlFragmentCompartment * _container;

    Q3PtrVector<UmlFragmentCompartment> _compartments;

    Q3CString _name;

    int _x;

    int _y;

    int _w;

    int _h;

    UmlDiagram * _refer;

    Q3CString _arguments;

    Q3PtrVector<UmlClassInstanceReference> _covered;

    // internal, don't call it
    void read_();


public:
    //internal, do NOT use it

    int vcenter_(int rank) const;

    //internal, do NOT use it

    void read_covered_(Q3PtrDict<UmlClassInstanceReference> & instances);

    // internal
    static UmlFragmentCompartment * get_container_(int x, int y, int w, int h, const Q3PtrVector<UmlFragment> & fragments);


private:
    // internal
    static void compute_container_(Q3PtrVector<UmlFragment> & fragments);


public:
    int w() const {
        return _w;
    }

    int h() const {
        return _h;
    }

    //  to avoid compiler warning, don't call it
    ~UmlBaseFragment();

    friend class UmlBaseUseCaseDiagramDefinition;
    friend class UmlBaseSequenceDiagramDefinition;
};

#endif
