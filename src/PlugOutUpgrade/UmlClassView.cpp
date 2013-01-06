#include "UmlClassView.h"

void UmlClassView::replace_friend()
{
    const Q3PtrVector<UmlItem> ch = children();
    unsigned i;

    for (i = 0; i != ch.size(); i += 1)
        ch[i]->replace_friend();
}
