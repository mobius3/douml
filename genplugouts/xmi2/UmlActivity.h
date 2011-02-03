#ifndef _UMLACTIVITY_H
#define _UMLACTIVITY_H


#include "UmlBaseActivity.h"
#include "FlowContainer.h"
#include <q3cstring.h>
#include <qmap.h>

class FileOut;
class UmlItem;

class UmlActivity : public UmlBaseActivity, public FlowContainer {
  public:
    //  the constructor, do not call it yourself !!!!!!!!!!
     UmlActivity(void * id, const Q3CString & s) : UmlBaseActivity(id, s) {
    }

    //write the definition if it is not empty for the target language
    virtual void write(FileOut & out);

    void write_condition(FileOut & out, Q3CString cond, bool pre);

    UmlItem * add_opaque_behavior(Q3CString beh, UmlItem * who, const char * k);

    UmlItem * add_opaque_expression(Q3CString val, UmlItem * who);


  private:
    struct Opaque {
        UmlItem * item;

        const char * kind;

        Opaque(){}

        Opaque(UmlItem * i, const char * k) : item(i), kind(k) {}

    };
    
    

  protected:
    QMap<Q3CString, Opaque> _opaque_behavior;

    QMap<Q3CString, UmlItem *> _opaque_expression;

};

#endif
