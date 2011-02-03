#ifndef _TOKEN_H
#define _TOKEN_H


#include <q3cstring.h>
#include <q3valuelist.h>

class FileIn;

//A token correspond to the information of a form <...> or <... /> or </...>
class Token {
  public:
    void read(FileIn & in, bool any);

    //return the work read just after <, may start by /
     const Q3CString & what() const;

    //return the value of the xmi:type
    const Q3CString & xmiType() const;

    //return the value of the xmi:id
    const Q3CString & xmiId() const;

    //return the value of the xmi:idref
    const Q3CString & xmiIdref() const;

    //return true if the token is </...>
    bool close() const;

    //return true if the token is </what>
    bool close(const char * what) const;

    //return true if the token is <.../>
    bool closed() const;

    //return the value associated to a key, "" if the couple doesn't exist
     const Q3CString & valueOf(Q3CString key) const;

    //return TRUE if the couple exist and set v with the value associated to a key
    bool valueOf(Q3CString key, Q3CString & v) const;


  private:
    //associate a key and a value
    struct Couple {
        Q3CString key;

        Q3CString value;

    };
    
    

  protected:
    Q3ValueList<Couple> _couples;

    //the work after < with out the / if it is </what>
    Q3CString _what;

    //true if the token is </..>
    bool _close;

    //true if the token is <../>
    bool _closed;

};

inline  const Q3CString & Token::what() const {
  return _what;
}

inline const Q3CString & Token::xmiType() const {
  return valueOf("xmi:type");
}

inline const Q3CString & Token::xmiId() const {
  return valueOf("xmi:id");
}

inline const Q3CString & Token::xmiIdref() const {
  return valueOf("xmi:idref");
}

inline bool Token::close() const {
  return _close;
}

inline bool Token::closed() const {
  return _closed;
}

#endif
