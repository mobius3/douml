
#include "UmlCom.h"
#include "UmlBaseMessage.h"
#include "UmlClassInstanceReference.h"
#include "UmlOperation.h"

void UmlBaseMessage::read_(const QHash<void*, UmlClassInstanceReference*> & instances)
{
    _operation = (UmlOperation *) UmlBaseItem::read_();

    if (_operation == 0) _form = UmlCom::read_string();

    _from = instances[reinterpret_cast<void*>(uintptr_t(UmlCom::read_unsigned()))];
    _to = instances[reinterpret_cast<void*>(uintptr_t(UmlCom::read_unsigned()))];
}

