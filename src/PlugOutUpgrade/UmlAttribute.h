#ifndef UMLATTRIBUTE_H
#define UMLATTRIBUTE_H

#include "UmlBaseAttribute.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'attribute', notes that the class 'UmlClassItem'
// is a mother class of the class's children.
// You can modify it as you want (except the constructor)

class UmlAttribute : public UmlBaseAttribute {
  public:
    UmlAttribute(void * id, const Q3CString & n)
      :  UmlBaseAttribute(id, n) {};
    
    static UmlAttribute * java2Php(UmlClass * php, UmlClass * java,
				   const char * javaname,
				   const char * phpname = 0);
    
    static UmlAttribute * java2Python(UmlClass * python, UmlClass * java,
				      const char * javaname,
				      const char * pythonname = 0);
    
    static UmlAttribute * cpp2Python(UmlClass * python, UmlClass * cpp,
				     const char * javaname,
				     const char * pythonname = 0);
};

#endif
