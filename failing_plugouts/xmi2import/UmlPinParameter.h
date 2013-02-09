#ifndef _UMLPINPARAMETER_H
#define _UMLPINPARAMETER_H


#include "UmlBasePinParameter.h"


class UmlPinParameter : public UmlBasePinParameter
{
protected:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlPinParameter(void * id, const WrapperStr & s) : UmlBasePinParameter(id, s) {
    }

};

#endif
