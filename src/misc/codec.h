// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

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
}inline QString toLocaleFull(const char*& p)
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    QString temp1 = codec->toUnicode(p);
    int size =  codec->fromUnicode(temp1).size();
    p+=size;
    return temp1;
}

#endif // CODEC_H
