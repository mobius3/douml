
#include "UmlClass.h"
#include "Context.h"
#include <QVector>
#include <QByteArray>

void UmlClass::change(Context & ctx)
{
    if (ctx.onClass() && ctx.match_stereotype(stereotype())) {
        if (ctx.cpp()) {
            const QByteArray & c = cppDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_CppDecl(ctx.replace(c)))
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

    const QVector<UmlItem*> ch = children();
    int i;

    for (i = 0; i != ch.size(); i += 1)
        ch[i]->change(ctx);

    unload(TRUE, TRUE);
}

