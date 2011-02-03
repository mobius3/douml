
#include "UmlAccessVariableValueAction.h"
#include "FileIn.h"
#include "Token.h"

#include "UmlCom.h"
//Added by qt3to4:
#include <Q3CString>
void UmlAccessVariableValueAction::import_it(FileIn & in, Token & token) {
  Q3CString s = token.valueOf("variable");
  
  if (! s.isEmpty())
    setVariable(s);
    
  if (! token.closed()) {
    Q3CString k = token.what();
    const char * kstr = k;
    
    while (in.read(), !token.close(kstr)) {
      s = token.what();
      
      if (s == "variable") {
	setVariable(token.xmiIdref());
	if (! token.closed())
	  in.finish("variable");
      }
      else
	import(in, token);
    }
  }
}

void UmlAccessVariableValueAction::setVariable(Q3CString idref) {
  QMap<Q3CString, UmlItem *>::Iterator it = All.find(idref);
  
  if (it == All.end())
    Unresolved::addRef(this, idref);
  else {
    switch ((*it)->kind()) {
    case anAttribute:
    case aRelation:
      set_Variable(*it);
    default:
      break;
    }
  }
}

void UmlAccessVariableValueAction::solve(Q3CString idref) {
  QMap<Q3CString, UmlItem *>::Iterator it = All.find(idref);
  
  if (it == All.end()) {
    if (!FileIn::isBypassedId(idref))
      UmlCom::trace("activity action : unknown variable reference '" + idref + "'<br>");
  }
  else {
    switch ((*it)->kind()) {
    case anAttribute:
    case aRelation:
      set_Variable(*it);
    default:
      break;
    }
  }
}

