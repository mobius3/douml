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

#ifndef CODADDMSGDIALOG_H
#define CODADDMSGDIALOG_H

#include <qdialog.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <Q3ValueList>

class Q3ComboBox;
class CodObjCanvas;
class CodMsgSupport;
class ColDiagramView;
class OperationData;
class BrowserClass;

class CodAddMsgDialog : public QDialog
{
    Q_OBJECT

protected:
    CodMsgSupport * in;
    ColDiagramView * view;
    bool forward;
    BrowserClass * cl;
    Q3ComboBox * cbrank;
    QStringList list;
    Q3ValueList<const OperationData *> opers;
    Q3ComboBox * edoper;

    static QSize previous_size;

public:
    CodAddMsgDialog(CodObjCanvas * fr, CodObjCanvas * t, CodMsgSupport * i,
                    ColDiagramView * v, bool f);
    virtual ~CodAddMsgDialog();

protected slots:
    void menu_op();
    virtual void polish();
    void accept();
};

#endif
