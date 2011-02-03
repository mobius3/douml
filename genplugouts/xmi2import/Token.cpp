
#include "Token.h"
#include "FileIn.h"
//Added by qt3to4:
#include <Q3CString>
#include <Q3ValueList>

void Token::read(FileIn & in, bool any) {
  _couples.clear();
  
  const char * k;
  BooL str;
  
  // bypass comment
  for (;;) {
    k = in.readWord(any, str);
    if (str || (*k != '<')) {
      if (any)
	continue;
      else
	in.error("'&lt;...' expected");
    }
    
    k = in.readWord(any, str);
    if (str || (*k != '!'))
      break;
    
    int minus = 0;
    
    for (;;) {
      char c = *in.readWord(TRUE, str);
      
      if (! str) {
	if (c == '-')
	  minus += 1;
	else if ((c == '>') && (minus == 2))
	  break;
	else
	  minus = 0;
      }
    }
  }


  char last;
  
  // note : k is not a string
  if (*k == '?') {
    last = '?';
    k = in.readWord(any, str);
  }
  else
    last = '/';
  
  if (!str && (*k == '/')) {
    _close = TRUE;
    k = in.readWord(any, str);
  }
  else
    _close = FALSE;
  
  if (str)
    in.error("syntax error \"" + Q3CString(k) + "\" unexpected");
    
  _what = k;
  
  while (k = in.readWord(any, str), str || (*k != '>')) {
    if (!str && (*k == last)) {
      k = in.readWord(any, str);
      if (str || (*k != '>'))
	in.error("syntax error near '" + Q3CString(k)  + "'>' expected");
      _closed = TRUE;
      return;
    }
    
    if (str) {
      if (!any)
	in.error("syntax error near '" + Q3CString(k) + "'");
    }
    else {
      Couple cpl;
      
      cpl.key = k;
      
      if (!any || !strcmp(k, "xmi:id")) {
	if (!any && !valueOf(k).isNull())
	  in.error("'" + cpl.key + "' duplicated");
	
	if ((*in.readWord(FALSE, str) != '=') || str) {
	  if (! any)
	    in.error("syntax error near '" + Q3CString(k) + "', '=' expected");
	}
	else {
	  cpl.value = in.readWord(FALSE, str);
	  if (str)
	    _couples.append(cpl);
	  else if (! any)
	    in.error("syntax error after '='");
	}
      }
    }
  }

  _closed = FALSE;
}

bool Token::close(const char * what) const {
  return _close && (_what == what);
}

const Q3CString & Token::valueOf(Q3CString key) const {
  Q3ValueList<Couple>::ConstIterator iter;
  
  for (iter = _couples.begin(); iter != _couples.end(); ++iter)
    if ((*iter).key == key)
      return (*iter).value;
			  
  static Q3CString null;
  
  return null;
}

bool Token::valueOf(Q3CString key, Q3CString & v) const {
  Q3ValueList<Couple>::ConstIterator iter;
  
  for (iter = _couples.begin(); iter != _couples.end(); ++iter) {
    if ((*iter).key == key) {
      v = (*iter).value;
      return TRUE;
    }
  }
			  
  return FALSE;
}

