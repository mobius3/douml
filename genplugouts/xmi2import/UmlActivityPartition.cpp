
#include "UmlCom.h"
#include "UmlActivityPartition.h"
#include "UmlItem.h"
#include "Token.h"
#include "FileIn.h"
//Added by qt3to4:
#include <Q3CString>

UmlItem * UmlActivityPartition::container(anItemKind kind, Token & token, FileIn & in) {
  switch (kind) {
  case aPartition:
    return this;
  default:
    return parent()->container(kind, token, in);
  }

}

void UmlActivityPartition::solve(Q3CString idref) {
  QMap<Q3CString, UmlItem *>::Iterator it = All.find(idref);
  
  if (it == All.end()) {
    if (!FileIn::isBypassedId(idref))
      UmlCom::trace("activity partition : unknown represented element '" + idref + "'<br>");
  }
  else
    set_Represents(*it);
}

void UmlActivityPartition::init()
{
  declareFct("group", "uml:ActivityPartition", &importIt);
  declareFct("subpartition", "uml:ActivityPartition", &importIt);

}

void UmlActivityPartition::importIt(FileIn & in, Token & token, UmlItem * where)
{
  where = where->container(aPartition, token, in);
    
  if (where != 0) {
    Q3CString s = token.valueOf("name");
    UmlActivityPartition * r = create(where, s);
    
    if (r == 0)
      in.error("cannot create activity partition '"
	       + s + "' in '" + where->name() + "'");
    
    r->addItem(token.xmiId(), in);
    
    if (token.valueOf("isdimension") == "true")
      r->set_isDimension(TRUE);
    
    if (token.valueOf("isexternal") == "true")
      r->set_isExternal(TRUE);
    
    Q3CString idref = token.valueOf("represents");
  
    if (! token.closed()) {
      Q3CString k = token.what();
      const char * kstr = k;
      
      while (in.read(), !token.close(kstr)) {
	s = token.what();
	
	if (s == "variable") {
	  idref = token.xmiIdref();
	  if (! token.closed())
	    in.finish("variable");
	}
	else
	  r->UmlItem::import(in, token);
      }
    }
    
    if (! idref.isEmpty()) {
      QMap<Q3CString, UmlItem *>::Iterator it = All.find(idref);
      
      if (it == All.end())
	Unresolved::addRef(r, idref);
      else
	r->set_Represents(*it);
    }
  }
}

