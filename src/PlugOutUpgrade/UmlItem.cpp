#include "UmlItem.h"

UmlItem::~UmlItem()
{
}

void UmlItem::rename_jdk5()
{
    const Q3PtrVector<UmlItem> ch = children();

    for (unsigned i = 0; i != ch.size(); i += 1)
        ch[i]->rename_jdk5();
}

void UmlItem::move_after(anItemKind k, const char * name)
{
    const Q3PtrVector<UmlItem> ch = parent()->children();
    unsigned i;

    for (i = 0; i != ch.size(); i += 1) {
        if ((ch[i]->kind() == k) &&
            (ch[i]->name() == name)) {
            moveAfter(ch[i]);
            break;
        }
    }
}

void UmlItem::replace_friend()
{
    // does nothing
}
