// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
//
// This file is part of the BOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : bouml@free.fr
// home   : http://bouml.free.fr
//
// *************************************************************************





#include <qstring.h>
//Added by qt3to4:
#include <Q3StrList>
#include <Q3CString>
#include "Logging/QsLog.h"

#include "mystr.h"
bool operator==(const WrapperStr & s1, const char * s2)
{
    return s1.s == QString::fromLatin1(s2);
}
bool operator==(const char * s1, const WrapperStr & s2)
{
    return s2.s == QString::fromLatin1(s1);
}
bool operator==(const WrapperStr & s1, const QString & s2)
{
    return s1.s == s2;
}

bool operator==(const QString & s1, const WrapperStr & s2)
{
    return s1 == s2.s;
}

bool operator!=(const WrapperStr & s1, const char * s2)
{
    return s1.s != QString::fromLatin1(s2);
}
bool operator!=(const char * s1, const WrapperStr & s2)
{
    return QString::fromLatin1(s1) != s2.s;
}
bool operator!=(const WrapperStr & s1, const QString & s2)
{
    return s1.s == s2;
}

bool operator!=(const QString & s1, const WrapperStr & s2)
{
    return s1 == s2.s;
}


QString operator+(const WrapperStr & s1, const char * s2)
{
    QLOG_INFO() << Q_FUNC_INFO;
    QLOG_INFO() << s1.s << " " << QString::fromLatin1(s2)<< Q_FUNC_INFO;
    return s1.s + QString::fromLatin1(s2);
}

QString operator+(const char * s1, const WrapperStr & s2)
{

    QLOG_INFO() << Q_FUNC_INFO;
    QLOG_INFO() << s2.s << " " << QString::fromLatin1(s1);
    return s2.s + QString::fromLatin1(s1);
}
QString operator+(const WrapperStr & s1, const QString & s2)
{
    QLOG_INFO() << Q_FUNC_INFO;
    QLOG_INFO() << s1.s << " " << s2 << Q_FUNC_INFO;
    return s1.s + s2;
}
QString operator+(const QString & s1, const WrapperStr & s2)
{
    QLOG_INFO() << Q_FUNC_INFO;
    QLOG_INFO() << s1 << " " << s2.s << Q_FUNC_INFO;
    return s1 + s2.s;
}

#if 0
#include <stdio.h>

void WrapperStr::statistics()
{
  int l[128];
  int n = 0;
  
  memset(l, 0, sizeof(l));
  
  int index = SHAREDDICTSIZE;
  
  while (index--) {
    int ln = shared[index].count();
    
    n += ln;
    l[(ln > 127) ? 127 : ln] += 1;
  }
  
  printf("%d strings\n", n);
  
  for (index = 0; index != 128; index += 1)
    if (l[index] != 0)
      printf("%d : %d\n", index, l[index]);
}
#endif

//
