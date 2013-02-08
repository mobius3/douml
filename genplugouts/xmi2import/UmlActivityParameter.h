#ifndef _UMLACTIVITYPARAMETER_H
#define _UMLACTIVITYPARAMETER_H


#include "UmlBaseActivityParameter.h"


class FileIn;
class Token;

class UmlActivityParameter : public UmlBaseActivityParameter
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlActivityParameter(void * id, const WrapperStr & s) : UmlBaseActivityParameter(id, s) {
    }

    void readParameter(FileIn & in, Token & token);

    void readParameterNode(FileIn & in, Token & token);


private:
    void setEffect(WrapperStr s, FileIn & in);

};

#endif
