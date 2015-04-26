
#include "UmlOperation.h"
#include "Context.h"
//Added by qt3to4:
#include <QByteArray>

void UmlOperation::change(Context & ctx)
{
    if (ctx.onOperation() && ctx.match_stereotype(stereotype())) {
        if (ctx.cpp()) {
            const QByteArray & c = cppDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_CppDecl(ctx.replace(c)))
                    ctx.err();
            }

            const QByteArray & f = cppDef();

            if (!f.isEmpty() && ctx.match(f)) {
                if (!set_CppDef(ctx.replace(f)))
                    ctx.err();
            }
        }

        if (ctx.java()) {
            const QByteArray & c = javaDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_JavaDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.php()) {
            const QByteArray & c = phpDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PhpDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.python()) {
            const QByteArray & c = pythonDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PythonDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.idl()) {
            const QByteArray & c = idlDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_IdlDecl(ctx.replace(c)))
                    ctx.err();
            }
        }
    }
}

