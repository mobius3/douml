/*
 * Copyright 2010 Mohammad Abdulfatah. All rights reserved.
 *
 * Licensed under the MIT license:
 *
 *     http://www.opensource.org/licenses/mit-license.php
 *
 */

#ifndef EVENTS_UTILITIES_TYPEIDENTIFIER_H_
#define EVENTS_UTILITIES_TYPEIDENTIFIER_H_

#include "GenerateTypeId.h"

template<typename T> class TypeIdentifier
{
public:
    static unsigned int id() {
#if defined (_MSC_VER)
        return GenerateTypeId(__FUNCTION__);
#elif defined(__GNUC__)
        return GenerateTypeId(__PRETTY_FUNCTION__);
#else
        return GenerateTypeId(typeid(T).name());
#endif
    }
private:
    TypeIdentifier();
};

#endif // EVENTS_UTILITIES_TYPEIDENTIFIER_H_
