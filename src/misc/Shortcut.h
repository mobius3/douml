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

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <qstringlist.h>
#include <qmap.h>

class Shortcut
{
public:
    static void init(bool conv);
    static const QStringList & cmds();
    static const QStringList & keys();

    static const QMap<QString, QString> & shortcuts();
    static QString extract(QString, BooL & shift, BooL & ctrl, BooL & alt);

    static QString shortcut(int key, int buttons);

    static void raz();
    static void add(QString k, bool shift, bool ctrl, bool alt, QString s);

    static void save();

private:
    static void load(bool conv);
};


#endif
