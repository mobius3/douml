#ifndef _FILE_H
#define _FILE_H


#include <qstring.h>
#include <QByteArray>
#include "aVisibility.h"
#include "Language.h"


#include <qfile.h>
enum { ATOM = 1, STRING = 2 };

class File : public QFile
{
public:
    File(QString s, QString here);

    bool open(int m);

    //// read a token in 's', returns its kind

    int read(QByteArray & s);

    //// e is expected, return TRUE if ok

    void read(const char * e);

    void unread(int k, const QByteArray & s);

    QByteArray context();


protected:
    int readString(QByteArray & s);

    int readMLString(QByteArray & s);

    int readAtom(QByteArray & s);


public:
    void syntaxError(const QByteArray s);

    void syntaxError(const QByteArray s, const QByteArray e);

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

    int readDefinitionBeginning(QByteArray & s, QByteArray & id, QByteArray & ste, QByteArray & doc, QHash<QByteArray, QByteArray*> & prop);

    void readProperties(QHash<QByteArray, QByteArray*> & d);


protected:
    int line_number;

    int unread_k;

    QByteArray unread_s;

};

#endif
