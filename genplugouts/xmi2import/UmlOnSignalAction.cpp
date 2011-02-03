
#include "UmlOnSignalAction.h"
#include "FileIn.h"
#include "Token.h"

#include "UmlCom.h"
#include "Sgnl.h"
//Added by qt3to4:
#include <Q3CString>
void UmlOnSignalAction::solve(Q3CString idref) {
  Q3CString sig = Signal::get(idref);
  
  if (!sig.isNull())
    set_Signal(sig);
  else if (!FileIn::isBypassedId(idref))
    UmlCom::trace("activity action : unknown signal reference '" + idref + "'<br>");

}

void UmlOnSignalAction::import_it(FileIn & in, Token & token) {
  Q3CString s = token.valueOf("signal");
  
  if (!s.isEmpty()) {
    Q3CString sig = Signal::get(s);
    
    if (!sig.isNull())
      set_Signal(sig);
    else
      Unresolved::addRef(this, s);
  }

  if (! token.closed()) {
    Q3CString k = token.what();
    const char * ks = k;
    
    while (in.read(), !token.close(ks)) {
      if (token.what() == "signal") {
	Q3CString sig_name;
	Q3CString sig_ref;
	
	Signal::add(in, token, sig_name, sig_ref);
	
	if (!sig_name.isNull())
	  set_Signal(sig_name);
	else
	  Unresolved::addRef(this, sig_ref);
      }
      else
	import(in, token);
    }
  }
}

