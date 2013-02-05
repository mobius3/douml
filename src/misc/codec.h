#ifndef CODEC_H
#define CODEC_H
#include "qstring.h"
#include "misc/mystr.h"
//#include
//#include "mystr.h"

extern QString codec();
extern void set_codec(QString);
extern QString toUnicode(const char *);
extern WrapperStr fromUnicode(const QString &);
extern bool hasCodec();
inline QString toLocale(const char*& p)
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    QString temp1 = codec->toUnicode(p).left(1);
    int size =  codec->fromUnicode(temp1).size();
    p+=size;
    return temp1;
}
#endif // CODEC_H
