#ifndef _FILEIN_H
#define _FILEIN_H


#include <qstring.h>
#include <q3cstring.h>
#include <q3dict.h>

#include <stdio.h>
#include <qmap.h>
class Token;

//to read in the file and extract 'Token'
class FileIn {
  public:
    FileIn(const QString & path, FILE * fp);

    ~FileIn();

    Token & read(bool any = FALSE);

    //return content and the next token which must be a 'what'
    Q3CString body(Q3CString what);

    //return the next work, may be :
    //<
    ///
    //>
    //=
    //!
    //-
    //?
    //a string without "
    //an identifier (forced to lower case)
    //
    //doesn't return on eof
    //
    //Warning : returned value will be changed by next call !
    const char * readWord(bool any, BooL & str);

    void finish(Q3CString what);

    void bypass(Token & tk);

    void bypassedId(Token & tk);

    //doesn't return
    void error(Q3CString s);

    void warning(Q3CString s);

    const Q3CString & path() const { return _path; }

    static bool isBypassedId(Q3CString id) {
      return BypassedIds[QString(id)] != 0;
    }


  protected:
    Q3CString _path;

    FILE * _fp;

    bool _utf8;

    int _linenum;

    int _length;

    char * _buffer;

    QMap<Q3CString, char> _special_chars;

    static Q3Dict<char> BypassedIds;


  private:
    const char * read_word(int c, bool any);

    const char * read_string(int marker);

    char read_special_char();


  public:
    void setEncoding(Q3CString s);

};

#endif
