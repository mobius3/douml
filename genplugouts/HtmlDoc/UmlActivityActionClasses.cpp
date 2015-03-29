
#include "UmlActivityActionClasses.h"

#include "UmlOperation.h"
//Added by qt3to4:
#include <QByteArray>
QByteArray UmlSendObjectAction::sKind()
{
    return "send object activity action";
}

void UmlSendObjectAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlUnmarshallAction::sKind()
{
    return "unmarshall activity action";
}

void UmlUnmarshallAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlSendSignalAction::sKind()
{
    return "send signal activity action";
}

QByteArray UmlBroadcastSignalAction::sKind()
{
    return "broadcast signal activity action";
}

QByteArray UmlValueSpecificationAction::sKind()
{
    return "value specification activity action";
}

void UmlValueSpecificationAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    QByteArray s = value();
    QByteArray scpp = cppValue();
    QByteArray sjava = javaValue();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Value :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlOpaqueAction::sKind()
{
    return "opaque activity action";
}

void UmlOpaqueAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    QByteArray s = behavior();
    QByteArray scpp = cppBehavior();
    QByteArray sjava = javaBehavior();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Behavior :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlAcceptEventAction::sKind()
{
    return "accept event activity action";
}

void UmlAcceptEventAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isUnmarshall()) {
        if (isTimeEvent())
            fw.write("<p>Unmarshall, event is a time event</p>");
        else
            fw.write("<p>Unmarshall</p>");
    }
    else if (isTimeEvent())
        fw.write("<p>Event is a time event</p>");

    QByteArray s = trigger();
    QByteArray scpp = cppTrigger();
    QByteArray sjava = javaTrigger();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Trigger :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlCallOperationAction::sKind()
{
    return "call operation activity action";
}

void UmlCallOperationAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isSynchronous())
        fw.write("<p>Is synchronous</p>");

    if (operation() != 0) {
        fw.write("<p>Operation : ");
        operation()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlCallBehaviorAction::sKind()
{
    return "call behavior activity action";
}

void UmlCallBehaviorAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isSynchronous())
        fw.write("<p>Is synchronous</p>");

    if (behavior() != 0) {
        fw.write("<p>Behavior : ");
        behavior()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlClearVariableValueAction::sKind()
{
    return "clear variable value activity action";
}

QByteArray UmlReadVariableValueAction::sKind()
{
    return "read variable value activity action";
}

QByteArray UmlWriteVariableValueAction::sKind()
{
    return "write variable value activity action";
}

QByteArray UmlAddVariableValueAction::sKind()
{
    return "add variable value activity action";
}

void UmlAddVariableValueAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isReplaceAll())
        fw.write("<p>Replace all</p>");

    if (variable() != 0) {
        fw.write("<p>Variable : ");
        variable()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlRemoveVariableValueAction::sKind()
{
    return "remove variable value activity action";
}

void UmlRemoveVariableValueAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isRemoveDuplicates())
        fw.write("<p>Remove duplicates</p>");

    if (variable() != 0) {
        fw.write("<p>Variable : ");
        variable()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlAcceptCallAction::sKind()
{
    return "accept call activity action";
}

void UmlAcceptCallAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    QByteArray s = trigger();
    QByteArray scpp = cppTrigger();
    QByteArray sjava = javaTrigger();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>Trigger :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlReplyAction::sKind()
{
    return "reply activity action";
}

void UmlReplyAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    QByteArray s = replyToCall();
    QByteArray scpp = cppReplyToCall();
    QByteArray sjava = javaReplyToCall();

    if (!s.isEmpty() || !scpp.isEmpty() || !sjava.isEmpty()) {
        fw.write("<p>replyToCall :</p><ul>");

        if (!s.isEmpty()) {
            fw.write("<li>OCL : <pre>\n");
            writeq(s);
            fw.write("</pre></li>");
        }

        if (!scpp.isEmpty()) {
            fw.write("<li>C++ : <pre>\n");
            writeq(scpp);
            fw.write("</pre></li>");
        }

        if (!sjava.isEmpty()) {
            fw.write("<li>Java : <pre>\n");
            writeq(sjava);
            fw.write("</pre></li>");
        }

        fw.write("</ul>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlCreateObjectAction::sKind()
{
    return "create object activity action";
}

void UmlCreateObjectAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (!classifier().isEmpty()) {
        fw.write("<p>Classifier : ");
        writeq(classifier());
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlDestroyObjectAction::sKind()
{
    return "destroy object activity action";
}

void UmlDestroyObjectAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isDestroyLinks()) {
        if (isDestroyOwnedObjects())
            fw.write("<p>Destroy links, destroy owned objects</p>");
        else
            fw.write("<p>Destroy links</p>");
    }
    else if (isDestroyOwnedObjects())
        fw.write("<p>Destroy owned objects</p>");

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlTestIdentityAction::sKind()
{
    return "test identity activity action";
}

void UmlTestIdentityAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlRaiseExceptionAction::sKind()
{
    return "raise exception activity action";
}

void UmlRaiseExceptionAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

QByteArray UmlReduceAction::sKind()
{
    return "reduce activity action";
}

void UmlReduceAction::html(QByteArray pfix, unsigned int rank, unsigned int level)
{
    UmlActivityAction::html();

    if (isOrdered())
        fw.write("<p>Ordered</p>");

    if (reducer() != 0) {
        fw.write("<p>Reducer : ");
        reducer()->write();
        fw.write("</p>");
    }

    write_children(pfix, rank, level);

    unload(FALSE, FALSE);
}

