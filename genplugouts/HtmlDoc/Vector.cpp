
#include "Vector.h"
#include "UmlItem.h"

void Vector::addElement(const UmlItem * x)
{
    if (v.capacity() == v.size())
        v.reserve(v.size() + 256);

    v.append(const_cast<UmlItem*>(x));
}

