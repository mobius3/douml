
#include "UmlClass.h"
#include "Context.h"
//Added by qt3to4:
#include <Q3CString>

void UmlClass::change(Context & ctx)
{
    if (ctx.onClass() && ctx.match_stereotype(stereotype())) {
        if (ctx.cpp()) {
            const Q3CString & c = cppDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_CppDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.java()) {
            const Q3CString & c = javaDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_JavaDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.php()) {
            const Q3CString & c = phpDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PhpDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.python()) {
            const Q3CString & c = pythonDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_PythonDecl(ctx.replace(c)))
                    ctx.err();
            }
        }

        if (ctx.idl()) {
            const Q3CString & c = idlDecl();

            if (!c.isEmpty() && ctx.match(c)) {
                if (!set_IdlDecl(ctx.replace(c)))
                    ctx.err();
            }
        }
    }

    const Q3PtrVector<UmlItem> ch = children();
    unsigned i;

    for (i = 0; i != ch.size(); i += 1)
        ch[i]->change(ctx);

    unload(TRUE, TRUE);
}

