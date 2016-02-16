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

#ifndef CLASSVIEWDIALOG_H
#define CLASSVIEWDIALOG_H

#include <tabdialog.h>
//Added by qt3to4:
//

#include "BrowserNode.h"

class QComboBox;
class LineEdit;
class MultiLineEdit;
class BasicData;
class KeyValuesTable;
class BodyDialog;

class ClassViewDialog : public TabDialog
{
    Q_OBJECT

protected:
    QWidget * umltab;
    BasicData * data;
    LineEdit * edname;
    QComboBox * edstereotype;
    QComboBox * deploymentview;
    BrowserNodeList deploymentviews;
    MultiLineEdit * comment;
    KeyValuesTable * kvtable;
    QList<BodyDialog *> edits;

    static QSize previous_size;

    static void post_edit_description(ClassViewDialog * d, QString s);

public:
    ClassViewDialog(BasicData * nd);
    virtual ~ClassViewDialog();

protected slots:
    virtual void polish();
    virtual void accept() override;
    void edit_description();

    void change_tabs(QWidget *);
};

#endif
