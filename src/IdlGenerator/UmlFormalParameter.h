#ifndef _UMLFORMALPARAMETER_H
#define _UMLFORMALPARAMETER_H


#include "UmlBaseFormalParameter.h"
//Added by qt3to4:
#include <Q3CString>
#include <QTextOStream>

class QTextOStream;

// This class manages 'formal parameters' of a template class. For instance 'T' in 
//
//	template class Cl<class T> ...
//
// You can modify it as you want (except the constructor)
class UmlFormalParameter : public UmlBaseFormalParameter {
  public:
    UmlFormalParameter() {};

    void generate(QTextOStream & f, Q3CString & s, const char *& sep) const;
};

#endif
