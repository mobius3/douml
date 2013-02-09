
#include "UmlClassMember.h"
//Added by qt3to4:
#include <Q3CString>

void UmlClassMember::setComment(Q3CString s)
{
    set_Description(((cppDecl().find("${description}") != -1) ? "// " : " ")
                    + s);

}

