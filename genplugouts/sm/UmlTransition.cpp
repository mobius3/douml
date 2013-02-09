
#include "UmlTransition.h"
#include "UmlClass.h"

#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3CString>

#include "UmlCom.h"
#include "UmlState.h"
#include "UmlOperation.h"

Q3CString UmlTransition::triggerName()
{
    // get & check trigger's name
    Q3CString s = cppTrigger();

    if (s.isEmpty()) {
        switch (parent()->kind()) {
        case anInitialPseudoState:
#ifndef WIN32
#warning to check
#endif
        case anEntryPointPseudoState:
            s = "create";
            break;

        case aState:
            s = "_completion";
            break;

        case anExitPointPseudoState:
            // note : not managed as a 'standard' completion
            // see UmlExitPointPseudoState class
            break;

        default:
#ifndef WIN32
#warning to check
#endif
            UmlCom::trace("Error : transition must have a trigger<br>");
            throw 0;
        }
    }
    else if ((parent()->kind() == anInitialPseudoState) ||
#ifndef WIN32
#warning to check
#endif
             (parent()->kind() == anEntryPointPseudoState)) {
        if (s != "create") {
            UmlCom::trace("Error : the transition from an 'initial' or 'entry point' pseudo state may only have the trigger 'create'<br>");
            throw 0;
        }
    }
    else if (s == "create") {
        UmlCom::trace("Error : only the transition from an 'initial' or 'entry point' pseudo state may have the trigger 'create'<br>");
        throw 0;
    }
    else if (s[0] == '_') {
        UmlCom::trace("Error : sorry, trigger's name can't start by a '_'<br>");
        throw 0;
    }

    return s;
}

void UmlTransition::init(UmlClass *, Q3CString, Q3CString, UmlState * state)
{
    if (triggerName() == "_completion")
        state->setHasCompletion();
}

void UmlTransition::generate(UmlClass * machine, UmlClass * anystate, UmlState * state)
{
    if (_already_managed)
        return;

    Q3CString s = triggerName();

    // group transitions having the same trigger
    const Q3PtrVector<UmlItem> ch = parent()->children();
    unsigned index = ch.findRef(this);
    Q3PtrList<UmlTransition> trs;
    UmlTransition * tr_no_guard = 0;

    if (cppGuard().isEmpty())
        tr_no_guard = this;
    else
        trs.append(this);

    while (++index != ch.count()) {
        if ((ch[index]->kind() == aTransition) &&
            (((UmlTransition *) ch[index])->triggerName() == s)) {
            if (!((UmlTransition *) ch[index])->cppGuard().isEmpty())
                trs.append((UmlTransition *) ch[index]);
            else if (tr_no_guard != 0) {
                UmlCom::trace("Error : several transitions from '" + parent()->name()
                              + "' don't have guard");
                throw 0;
            }
            else
                tr_no_guard = (UmlTransition *) ch[index];

            ((UmlTransition *) ch[index])->_already_managed = TRUE;
        }
    }

    if (tr_no_guard != 0)
        // place it at end
        trs.append(tr_no_guard);

    // made the trigger

    UmlOperation * trg = state->assocClass()->trigger(s, machine, anystate);
    Q3CString body;

    if (s == "create") {
        // manage entry
        if (!state->cppEntryBehavior().isEmpty())
            body = "  _doentry(stm);\n";
    }

    if (!state->cppDoActivity().isEmpty())
        // state do activity before each event except create
        body += "  _do(stm);\n";

    bool completion = (s == "_completion");

    if (!completion && state->isLeaf() && state->hasCompletion())
        // manage completion
        body += "  if (_completion(stm)) return;\n";

    UmlTransition::generate(trs, machine, anystate, state,
                            body, "  ", completion);

    trg->set_CppBody(body);
}

void UmlTransition::generate(UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent)
{
    if (!cppTrigger().isEmpty()) {
        UmlCom::trace("Error : transition from a pseudo state can't have trigger<br>");
        throw 0;
    }

    Q3PtrList<UmlTransition> l;

    l.append(this);
    generate(l, machine, anystate, state, body, indent, FALSE);
}

void UmlTransition::generate(Q3PtrList<UmlTransition> trs, UmlClass * machine, UmlClass * anystate, UmlState * state, Q3CString & body, Q3CString indent, bool completion)
{
    UmlTransition * tr;
    bool guard = FALSE;

    for (tr = trs.first(); tr != 0; tr = trs.next()) {
        body += indent;

        if (!tr->cppGuard().isEmpty()) {
            // manage guard
            body += ((tr == trs.getFirst()) ? "if (" : "else if (")
                    + tr->cppGuard() + ") {\n";
            guard = TRUE;
        }
        else
            // no gard : it is the last transition, may be the first
            body += ((tr == trs.getFirst()) ? "{\n" : "else {\n");

        // the target state
        UmlItem * tg = tr->target();
        bool self_external = (state == tg) && tr->isExternal();

        while (tg->kind() != aState)
            tg = tg->parent();

        // the parent common to the current and the target state
        UmlState * common = state;

        if (self_external) {
            // execute exit behavior
            if (!state->cppExitBehavior().isEmpty())
                body += indent + "  _doexit(stm);\n";
        }
        else {
            bool fromExit =
                // the exit behavior is made entering in the exit point
                (tr->parent()->kind() == anExitPointPseudoState);

            // compute common parent and manage exit behavior
            if (tr->target()->kind() != aTerminatePseudoState) {
                while (!((UmlState *) tg)->inside(common)) {
                    if (!fromExit && !common->cppExitBehavior().isEmpty())
                        body += indent + "  stm" + common->path() + "._doexit(stm);\n";

                    fromExit = FALSE;

                    switch (common->parent()->kind()) {
                    case aState:
                        common = (UmlState *) common->parent();
                        break;

                    case aRegion:
                        common = (UmlState *) common->parent()->parent();
                        break;

                    default:
                        UmlCom::trace("Error : transition from '" + state->name()
                                      + "' goes outside the state machine");
                        throw 0;
                    }
                }
            }
        }

        // manage transition activity
        if (!tr->cppActivity().isEmpty())
            body += "#ifdef VERBOSE_STATE_MACHINE\n" + indent +
                    "  puts(\"DEBUG : execute activity of transition " + tr->name() +
                    "\");\n#endif\n" + tr->cppActivity();

        // manage entry behavior
        if (self_external) {
            if (state->needCreate())
                body += indent + "  create(stm);\n";
        }
        else if (tr->target()->kind() != aTerminatePseudoState) {
            if (tg != common) {
                Q3CString enter;
                UmlState * tg_parent;

                // the enter behavior of the target state will be managed
                // generating a call to create
                for (tg_parent = (UmlState *) tg->parent();
                     tg_parent != common;
                     tg_parent = (UmlState *) tg_parent->parent())
                    if (!tg_parent->cppEntryBehavior().isEmpty())
                        enter.insert(0,
                                     (const char *)(indent + "  stm" + tg_parent->path() + "._doentry(stm);\n")); //[rageek] ambiguous

                if (!enter.isEmpty())
                    body += enter;
            }

            // set the current state if needed
            if (tg != state)
                body += indent + "  stm._set_currentState(stm"
                        + ((UmlState *) tg)->path() + ");\n#ifdef VERBOSE_STATE_MACHINE\n" +
                        indent + "  puts(\"DEBUG : current state is now " + ((UmlState *) tg)->prettyPath() +
                        "\");\n#endif\n";
        }

        // do the transition
        if (tr->target()->kind() == aState) {
            if ((tg != state) && ((UmlState *) tg)->needCreate())
                body += indent + "  stm"
                        + ((UmlState *) tg)->path() + ".create(stm);\n";
        }
        else
            tr->target()->generate(machine, anystate, ((UmlState *) tg), body, indent + "  ");

        if (completion)
            body += indent + "  return (bool) 1;\n";

        body += indent + "}\n";
    }

    if (completion && guard)
        body += indent + "return (bool) 0;\n";
}

