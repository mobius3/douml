
#include "UmlTransition.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlItem.h"

#include "UmlCom.h"
#include "Trigger.h"
//Added by qt3to4:
#include "misc/mystr.h"
#include <Q3ValueList>
void UmlTransition::init()
{
    declareFct("transition", "uml:Transition", &importIt);
    declareFct("transition", "", &importIt);  // Borland Together 2006 for Eclipse

    Trigger::init();
}

void UmlTransition::solveThem()
{
    Q3ValueList<Transition>::Iterator iter;

    for (iter = All.begin(); iter != All.end(); ++iter) {
        Transition & transition = *iter;

        QMap<QString, UmlItem *>::Iterator isrc = UmlItem::All.find(transition.source);
        QMap<QString, UmlItem *>::Iterator itgt = UmlItem::All.find(transition.target);

        if ((isrc == UmlItem::All.end()) /*&&
	((isrc = Outgoings.find(transition.id)) == Outgoings.end())*/) {
            if (!FileIn::isBypassedId(transition.source))
                UmlCom::trace("transition '" + transition.id + "' : unknown source reference '" + transition.source + "'<br>");
        }
        else if ((itgt == UmlItem::All.end()) /*&&
	     ((itgt = Incomings.find(transition.id)) == Incomings.end())*/) {
            if (!FileIn::isBypassedId(transition.target))
                UmlCom::trace("transition '" + transition.id + "' : unknown target reference '" + transition.target + "'<br>");
        }
        else {
            UmlTransition * t = UmlTransition::create(*isrc, *itgt);

            if (t == 0)
                UmlCom::trace("cannot create transition '" + transition.id + "'<br>");
            else {
                UmlItem::All.insert(transition.id, t);

                if (! transition.name.isEmpty())
                    t->set_Name(transition.name);

                if (! transition.effect.isEmpty())
                    t->set_Activity(transition.effect);

                if (! transition.trigger.isEmpty())
                    t->set_Trigger(transition.trigger);
                else if (! transition.triggerRef.isEmpty()) {
                    WrapperStr trig = Trigger::get(transition.triggerRef);

                    if (!trig.isNull())
                        t->set_Trigger(trig);
                    else if (!FileIn::isBypassedId(transition.triggerRef))
                        UmlCom::trace("transition '" + transition.id + "' : unknown trigger reference '" + transition.triggerRef + "'<br>");
                }

                if (! transition.guard.isEmpty())
                    t->set_Guard(transition.guard);

                if (*isrc == *itgt)
                    t->set_IsExternal(transition.kind == "external");

                t->unload(FALSE, FALSE);
            }
        }
    }

    All.clear();
}

void UmlTransition::importIt(FileIn & in, Token & token, UmlItem *)
{
    Transition & transition = *(All.append(Transition()));
    WrapperStr s;

    transition.id = token.xmiId();
    transition.name = token.valueOf("name");
    transition.source = token.valueOf("source");
    transition.target = token.valueOf("target");
    transition.triggerRef = token.valueOf("trigger");
    transition.kind = token.valueOf("kind");

    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;

        while (in.read(), !token.close(kstr)) {
            s = token.what();

            if (s == "trigger")
                Trigger::add(in, token, transition.trigger, transition.triggerRef);
            else if (s == "guard") {
                if (! token.closed()) {
                    while (in.read(), !token.close("guard")) {
                        WrapperStr s = token.what();

                        if (s == "specification") {
                            transition.guard = token.valueOf("body");

                            if (transition.guard.isNull())
                                transition.guard = token.valueOf("value");	// UMODEL

                            if (! token.closed()) {
                                while (in.read(), !token.close("specification")) {
                                    WrapperStr s = token.what();

                                    if (s == "body")
                                        transition.guard = in.body("body");
                                    else if (! token.closed())
                                        in.finish(s);
                                }
                            }
                        }
                        else if (! token.closed())
                            in.finish(s);
                    }
                }
            }
            else if (s == "effect") {
                WrapperStr b = token.valueOf("body");

                if (! b.isNull()) {
                    transition.effect = b;

                    if (! token.closed())
                        in.finish(s);
                }
                else if (! token.closed()) {
                    while (in.read(), !token.close("effect")) {
                        b = token.what();

                        if (b == "body") {
                            transition.effect = in.body("body");
                            in.finish(s);
                            break;
                        }
                        else if (! token.closed())
                            in.finish(b);
                    }
                }
            }
            else if (! token.closed())
                in.finish(s);
        }
    }
}

Q3ValueList<UmlTransition::Transition> UmlTransition::All;

