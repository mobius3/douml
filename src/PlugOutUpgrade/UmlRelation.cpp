#include "UmlRelation.h"
#include "UmlClass.h"
#include "UmlCom.h"
//Added by qt3to4:
#include <Q3CString>

UmlRelation * UmlRelation::java2Php(UmlClass * php, UmlClass * java,
				    const char * name)
{
  UmlRelation * from = java->get_relation(name);
  
  if (from == 0) {
    Q3CString err = Q3CString("cannot find relation '") + 
      name + Q3CString("' in class '") + java->name()
	+ Q3CString("'<br>\n");
    UmlCom::trace(err);
    throw 0;
  }
  
  UmlRelation * to = 
    UmlBaseRelation::create(from->relationKind(), php, from->roleType());
  
  if (to == 0) {
    Q3CString err = Q3CString("cannot create relation '") + 
      name + Q3CString("' in class '") + php->name()
	+ Q3CString("'<br>\n");
    UmlCom::trace(err);
    throw 0;
  }
  
  UmlCom::trace("add relation " + php->name() + "::" + name + "<br>\n");

  to->set_RoleName(name);
  to->set_Multiplicity(from->multiplicity());
  to->set_isClassMember(from->isClassMember());
  to->set_Visibility(from->visibility());
  to->set_CppVisibility(from->cppVisibility());
  to->set_CppDecl(from->cppDecl());
  to->set_JavaDecl(from->javaDecl());
  
  return to;
}
