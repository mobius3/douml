
#include "UmlCom.h"
#include "UmlBaseFragmentCompartment.h"
#include "UmlBaseFragment.h"
//Added by qt3to4:
#include "misc/mystr.h"

void UmlBaseFragmentCompartment::add_contained_(UmlFragment * x)
{
    _contained.resize(_contained.size() + 1);
    _contained.insert(_contained.size() - 1, x);
}

void UmlBaseFragmentCompartment::add_text_(WrapperStr x)
{
    _texts.resize(_texts.size() + 1);
    _texts.insert(_texts.size() - 1, strdup(x));
}

void UmlBaseFragmentCompartment::add_cont_(WrapperStr s, int cy)
{
    if (cy < _fragment->vcenter_(_rank))
        _start_continuation = s;
    else
        _end_continuation = s;
}

bool UmlBaseFragmentCompartment::smaller(const UmlBaseFragmentCompartment * x) const
{
    return ((_fragment->w() < x->_fragment->w()) &&
            (_fragment->h() < x->_fragment->h()));
}

void UmlBaseFragmentCompartment::read_(UmlBaseFragment * fragment, int rank)
{
    _fragment = (UmlFragment *) fragment;
    _rank = rank;
    _y = UmlCom::read_unsigned();
}

UmlBaseFragmentCompartment::~UmlBaseFragmentCompartment()
{
}

