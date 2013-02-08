
#include "Sgnl.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlItem.h"
//Added by qt3to4:
#include "misc/mystr.h"

void Signal::init()
{
    UmlItem::declareFct("ownedmember", "uml:Signal", &importIt);
    UmlItem::declareFct("packagedelement", "uml:Signal", &importIt);
    UmlItem::declareFct("signal", "uml:Signal", &importIt);

}

void Signal::importIt(FileIn & in, Token & token, UmlItem *)
{
    All.insert(token.xmiId(), token.valueOf("name"));

    if (! token.closed())
        in.finish(token.what());
}

WrapperStr Signal::get(WrapperStr idref)
{
    QMap<QString, WrapperStr>::Iterator iter = All.find(idref);
    static WrapperStr null_str;

    return (iter == All.end()) ? null_str : *iter;
}

void Signal::add(FileIn & in, Token & token, WrapperStr & name, WrapperStr & idref)
{
    // token is <signal ...>
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

QMap<QString, WrapperStr> Signal::All;

