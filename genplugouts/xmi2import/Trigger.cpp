
#include "Trigger.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlItem.h"
//Added by qt3to4:
#include "misc/mystr.h"

void Trigger::init()
{
    UmlItem::declareFct("ownedmember", "uml:Trigger", &importIt);
    UmlItem::declareFct("packagedelement", "uml:Trigger", &importIt);
    UmlItem::declareFct("trigger", "uml:Trigger", &importIt);

    UmlItem::declareFct("ownedtrigger", "uml:AnyTrigger", &importIt); // Borland Together 2006 for Eclipse
}

void Trigger::importIt(FileIn & in, Token & token, UmlItem *)
{
    All.insert(token.xmiId(), token.valueOf("name"));

    if (! token.closed())
        in.finish(token.what());
}

WrapperStr Trigger::get(WrapperStr idref)
{
    QMap<QString, WrapperStr>::Iterator iter = All.find(idref);
    static WrapperStr null_str;

    return (iter == All.end()) ? null_str : *iter;
}

void Trigger::add(FileIn & in, Token & token, WrapperStr & name, WrapperStr & idref)
{
    // token is <trigger ...>
    WrapperStr t = token.xmiIdref();

    if (! t.isEmpty()) {
        QMap<QString, WrapperStr>::Iterator iter = All.find(t);

        if (iter == All.end()) {
            idref = t;
            name = "";
        }
        else {
            name = *iter;
            idref = "";
        }
    }
    else {
        name = token.valueOf("name");
        idref = "";
        All.insert(token.xmiId(), name);
    }

    if (! token.closed())
        in.finish(token.what());

}

QMap<QString, WrapperStr> Trigger::All;

