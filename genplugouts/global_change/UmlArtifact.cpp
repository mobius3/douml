
#include "UmlArtifact.h"
#include "Context.h"
//Added by qt3to4:
#include <Q3CString>

void UmlArtifact::change(Context & ctx)
{
    if (ctx.onArtifact() && ctx.match_stereotype(stereotype())) {
        if (ctx.cpp()) {
            const Q3CString & h = cppHeader();

            if (!h.isEmpty() && ctx.match(h)) {
                if (!set_CppHeader(ctx.replace(h)))
                    ctx.err();
            }

            const Q3CString & c = cppSource();

            if (!h.isEmpty() && ctx.match(c)) {
                if (!set_CppSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.java()) {
            const Q3CString & c = javaSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_JavaSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.php()) {
            const Q3CString & c = phpSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PhpSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.python()) {
            const Q3CString & c = pythonSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PythonSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.idl()) {
            const Q3CString & c = idlSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_IdlSource(ctx.replace(c)))
                    ctx.err();
            }
        }
    }
}

