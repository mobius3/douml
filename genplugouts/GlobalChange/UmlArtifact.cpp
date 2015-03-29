
#include "UmlArtifact.h"
#include "Context.h"
//Added by qt3to4:
#include <QByteArray>

void UmlArtifact::change(Context & ctx)
{
    if (ctx.onArtifact() && ctx.match_stereotype(stereotype())) {
        if (ctx.cpp()) {
            const QByteArray & h = cppHeader();

            if (!h.isEmpty() && ctx.match(h)) {
                if (!set_CppHeader(ctx.replace(h)))
                    ctx.err();
            }

            const QByteArray & c = cppSource();

            if (!h.isEmpty() && ctx.match(c)) {
                if (!set_CppSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.java()) {
            const QByteArray & c = javaSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_JavaSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.php()) {
            const QByteArray & c = phpSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PhpSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.python()) {
            const QByteArray & c = pythonSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PythonSource(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.idl()) {
            const QByteArray & c = idlSource();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_IdlSource(ctx.replace(c)))
                    ctx.err();
            }
        }
    }
}

