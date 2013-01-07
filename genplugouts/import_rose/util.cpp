#include "q3cstring.h"

#include "util.h"

Q3CString legalName(Q3CString s)
{
    for (unsigned index = 0; index != s.length(); index += 1) {
        char c = s.at(index);

        if ((c != '_') &&
            !((c >= 'a') && (c <= 'z')) &&
            !((c >= 'A') && (c <= 'Z')) &&
            !((c >= '0') && (c <= '9'))) {
            s.replace(index, 1, "__");
            index += 1;
        }
    }

    return s;
}

Q3CString replace(Q3CString f, Q3CString k, Q3CString v)
{
    int index = f.find(k);

    return (index != -1)
           ? f.replace(index, k.length(), v)
           : f;
}

bool isSep(int c)
{
    return ((c != '_') &&
            !((c >= 'a') && (c <= 'z')) &&
            !((c >= 'A') && (c <= 'Z')) &&
            !((c >= '0') && (c <= '9')));
}
