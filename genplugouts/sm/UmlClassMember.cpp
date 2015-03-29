
#include "UmlClassMember.h"
//Added by qt3to4:
#include <QByteArray>

void UmlClassMember::setComment(QByteArray s)
{
    set_Description(((cppDecl().indexOf("${description}") != -1) ? "// " : " ")
                    + s);

}

