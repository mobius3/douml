#ifndef CODEC_H
#define CODEC_H
#include "qstring.h"
#include "misc/mystr.h"
//#include "mystr.h"

extern QString codec();
extern void set_codec(QString);
extern QString toUnicode(const char *);
extern WrapperStr fromUnicode(const QString &);
extern bool hasCodec();

#endif // CODEC_H
