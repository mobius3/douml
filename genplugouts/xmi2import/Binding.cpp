
#include "Binding.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlClass.h"

#include "UmlCom.h"
//Added by qt3to4:
#include "misc/mystr.h"
void Binding::import(FileIn & in, Token & token, UmlClass * where)
{
    Q3PtrList<Binding> l;
    WrapperStr boundid = token.valueOf("boundelement");
    WrapperStr signatureid = token.valueOf("signature");

    if (! token.closed()) {
        WrapperStr k = token.what();
        const char * kstr = k;

        while (in.read(), !token.close(kstr)) {
            WrapperStr s = token.what();

            if (s == "boundelement")
                boundid = token.xmiIdref();
            else if (s == "signature")
                signatureid = token.xmiIdref();
            else if (s == "parametersubstitution") {
                WrapperStr formalid = token.valueOf("formal");
                WrapperStr actualid = token.valueOf("actual");
                WrapperStr actual;
                bool owned = FALSE;

                if (! token.closed()) {
                    while (in.read(), !token.close("parametersubstitution")) {
                        s = token.what();

                        if (s == "formal")
                            formalid = token.xmiIdref();
                        else if (s == "actual")
                            actualid = token.xmiIdref();
                        else if (s == "ownedactual") {
                            if (token.xmiType() == "uml:OpaqueExpression") {
                                WrapperStr opid = token.xmiId();

                                UmlItem::importOpaqueDef(in, token, 0);
                                owned = TRUE;

                                QMap<QString, WrapperStr>::Iterator it =
                                    UmlItem::OpaqueDefs.find(opid);

                                if (it != UmlItem::OpaqueDefs.end())
                                    actual = *it;

                                continue;
                            }
                        }

                        if (! token.closed())
                            in.finish(s);
                    }
                }

                if (!formalid.isEmpty() && (!actualid.isEmpty() || owned)) {
                    Binding * b = new Binding;

                    l.append(b);
                    b->boundId = boundid;
                    b->formalId = formalid;

                    if (owned)
                        b->actual = actual;
                    else
                        b->actualId = actualid;
                }
            }
        }
    }

    if (signatureid.isEmpty())
        in.warning("templateBinding : signature reference is missing");
    else if (! l.isEmpty()) {
        if (boundid.isEmpty())
            boundid = where->id();

        do {
            Binding * b = l.take(0);

            b->boundId = boundid;
            b->signatureId = signatureid;
            All.append(b);
        }
        while (! l.isEmpty());
    }
}

void Binding::solveThem()
{
    while (! All.isEmpty()) {
        Binding * b = All.take(0);

        QMap<QString, UmlItem *>::Iterator it = UmlItem::All.find(b->boundId);
        UmlClass * tmpl = UmlClass::signature(b->signatureId);

        if (it == UmlItem::All.end()) {
            if (!FileIn::isBypassedId(b->boundId))
                UmlCom::trace("templateBinding : unknown boundElement reference '" + b->boundId + "'<br>");
        }
        else if ((*it)->kind() != aClass)
            UmlCom::trace("templateBinding : boundElement reference '" + b->boundId + "' is not a class<br>");
        else if (tmpl == 0) {
            if (!FileIn::isBypassedId(b->signatureId))
                UmlCom::trace("templateBinding : unknown signature reference '" + b->signatureId + "'<br>");
        }
        else if (((UmlClass *) *it)->bind(tmpl)) {
            UmlClass * cl = (UmlClass *) *it;

            int rank = tmpl->formalRank(b->formalId);

            if (rank != -1) {
                UmlTypeSpec typespec;

                if (b->actualId.isEmpty()) {
                    typespec.explicit_type = b->actual;
                    cl->replaceActual(rank, typespec);
                }
                else {
                    QMap<QString, WrapperStr>::Iterator opit =
                        UmlItem::OpaqueDefs.find(b->actualId);

                    if (opit != UmlItem::OpaqueDefs.end())
                        typespec.explicit_type = *opit;
                    else if ((it = UmlItem::All.find(b->actualId)) == UmlItem::All.end()) {
                        if (!FileIn::isBypassedId(b->actualId))
                            UmlCom::trace("templateBinding : unknown actual reference '" + b->actualId + "'<br>");
                    }
                    else if ((*it)->kind() != aClass)
                        UmlCom::trace("templateBinding : actual reference '" + b->actualId + "' kind not managed<br>");
                    else {
                        typespec.type = (UmlClass *) *it;
                        cl->replaceActual(rank, typespec);
                    }
                }
            }
        }

        delete b;
    }

}

Q3PtrList<Binding> Binding::All;

