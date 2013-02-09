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

#ifndef SOURCEDIALOG_H
#define SOURCEDIALOG_H

#include <qdialog.h>
//Added by qt3to4:
#include <QEvent>
#include <QLabel>

#include "DialogUtil.h"

class QLabel;

class NumberedMultiLineEdit : public MultiLineEdit
{
    Q_OBJECT

public:
    NumberedMultiLineEdit(QWidget * w) : MultiLineEdit(w) { };

protected:
    virtual bool event(QEvent * e);

signals:
    void cursorMoved(int l, int c);
};

class SourceDialog : public QDialog
{
    Q_OBJECT

protected:
    NumberedMultiLineEdit * e;
    QLabel * lineColumn;
    QString path;
    BooL & edited;
    unsigned & edition_number;

    static QSize previous_size;

public:
    SourceDialog(QString p, BooL & flg, unsigned & edn);
    virtual ~SourceDialog();

protected slots:
    void edit();
    void updateCursorPos(int l, int c);
};

#endif

