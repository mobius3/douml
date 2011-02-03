
#include "Sgnl.h"
#include "FileIn.h"
#include "Token.h"
#include "UmlItem.h"
//Added by qt3to4:
#include <Q3CString>

void Signal::init()
{
  UmlItem::declareFct("ownedmember", "uml:Signal", &importIt);
  UmlItem::declareFct("packagedelement", "uml:Signal", &importIt);
  UmlItem::declareFct("signal", "uml:Signal", &importIt);

}

void Signal::importIt(FileIn & in, Token & token, UmlItem *)
{
  All.insert(token.xmiId(), token.valueOf("name"));
      
  if (! token.closed())
    in.finish(token.what());
}

Q3CString Signal::get(Q3CString idref)
{
  QMap<Q3CString, Q3CString>::Iterator iter = All.find(idref);
  static Q3CString null_str;
  
  return (iter == All.end()) ? null_str : *iter;
}

void Signal::add(FileIn & in, Token & token, Q3CString & name, Q3CString & idref)
{
  // token is <signal ...>
  Q3CString t = token.xmiIdref();
  
  if (! t.isEmpty()) {
    QMap<Q3CString, Q3CString>::Iterator iter = All.find(t);
    
    if (iter == All.end()) {
      idref = t;
      name = "";
    }
    else {
      name = *iter;
      idref = "";
    }
  }
  else {
    name = token.valueOf("name");
    idref = "";
    All.insert(token.xmiId(), name);
  }

  if (! token.closed())
    in.finish(token.what());

}

QMap<Q3CString, Q3CString> Signal::All;

