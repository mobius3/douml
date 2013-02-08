
#include "UmlCom.h"
#include "UmlBaseClassInstanceReference.h"
#include "UmlClass.h"
#include "UmlClassInstance.h"
//Added by qt3to4:
#include <Q3CString>

UmlClass * UmlBaseClassInstanceReference::type() const
{
    return (_instance) ? _instance->type() : _class;
}

const Q3CString & UmlBaseClassInstanceReference::name() const
{
    return (_instance) ? _instance->name() : _name;
}

void UmlBaseClassInstanceReference::read_()
{
    _instance = (UmlClassInstance *) UmlBaseItem::read_();

    if (_instance == 0) {
        _name = UmlCom::read_string();
        _class = (UmlClass *) UmlBaseItem::read_();
    }
}

