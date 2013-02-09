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

#ifndef INSTANCEDIALOG_H
#define INSTANCEDIALOG_H

#include <qdialog.h>
#include <qstringlist.h>

#include "BrowserNode.h"

class Q3ComboBox;
class LineEdit;
class Instance;

class InstanceDialog : public QDialog
{
    Q_OBJECT

protected:
    Instance * inst;
    QString what;
    UmlCode kind;
    QStringList list;
    BrowserNodeList nodes;
    LineEdit * edname;
    Q3ComboBox * edtype;

    static QSize previous_size;

public:
    InstanceDialog(Instance * a, QString w, UmlCode k);
    virtual ~InstanceDialog();

protected slots:
    void menu_type();
    virtual void polish();
    void accept();
};

#endif
