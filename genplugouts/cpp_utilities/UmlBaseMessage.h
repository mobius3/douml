#ifndef _UMLBASEMESSAGE_H
#define _UMLBASEMESSAGE_H


#include <q3cstring.h>
#include <q3ptrdict.h>

class UmlClassInstanceReference;
class UmlOperation;

// this class manages messages indenpendently of the diagram
class UmlBaseMessage
{
public:
    // return the instance sending the message
    UmlClassInstanceReference * from() const {
        return _from;
    }

    // return the instance receiving the message
    UmlClassInstanceReference * to() const {
        return _to;
    }

    // return the operation or 0/null,
    // exclusive with form()
    UmlOperation * operation() const {
        return _operation;
    }

    // return message as a string, may be empty/null,
    // exclusive with operation()
    const Q3CString & form() const {
        return _form;
    }


private:
    UmlClassInstanceReference * _from;

    UmlClassInstanceReference * _to;

    UmlOperation * _operation;

    Q3CString _form;

    // internal, don't call it
    void read_(const Q3PtrDict<UmlClassInstanceReference> & instances);

    friend class UmlBaseSequenceMessage;
    friend class UmlBaseCollaborationMessage;
};

#endif
