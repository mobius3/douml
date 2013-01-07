#ifndef _FILE_H
#define _FILE_H


#include <qstring.h>
#include <q3cstring.h>
#include "aVisibility.h"
#include "Language.h"
#include <q3dict.h>

#include <qfile.h>
enum { ATOM = 1, STRING = 2 };

class File : public QFile
{
public:
    File(QString s, QString here);

    bool open(int m);

    //// read a token in 's', returns its kind

    int read(Q3CString & s);

    //// e is expected, return TRUE if ok

    void read(const char * e);

    void unread(int k, const Q3CString & s);

    Q3CString context();


protected:
    int readString(Q3CString & s);

    int readMLString(Q3CString & s);

    int readAtom(Q3CString & s);


public:
    void syntaxError(const Q3CString s);

    void syntaxError(const Q3CString s, const Q3CString e);

    //// skip the end of the current block
    //// '(' already read
    void skipBlock();

    //// skip the next form

    void skipNextForm();

    void eof();

    void rewind();

    aVisibility readVisibility();

    bool readBool();

    Language readLanguage();

    int readDefinitionBeginning(Q3CString & s, Q3CString & id, Q3CString & ste, Q3CString & doc, Q3Dict<Q3CString> & prop);

    void readProperties(Q3Dict<Q3CString> & d);


protected:
    int line_number;

    int unread_k;

    Q3CString unread_s;

};

#endif
