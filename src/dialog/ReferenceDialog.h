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

#ifndef REFERENCE_DIALOG_H
#define REFERENCE_DIALOG_H

#include <qdialog.h>

#include "BrowserNode.h"

class Q3ComboBox;

class ReferenceDialog : public QDialog
{
    Q_OBJECT

protected:
    BrowserNode * target;
    BrowserNodeList nodes;
    Q3ComboBox * results;
    QPushButton * select_b;
    QPushButton * mark_unmark_b;
    QPushButton * mark_them_b;
    QPushButton * unmark_all_b;

    static ReferenceDialog * the;
    static QSize previous_size;

public:
    ReferenceDialog(BrowserNode * bn);
    virtual ~ReferenceDialog();

    static ReferenceDialog * get() {
        return the;
    }
    static void show(BrowserNode * target);

    void update();

protected slots:
    virtual void polish();
    void compute();
    void select();
    void selected(int);
    void mark_unmark();
    void mark_them();
    void unmark_all();
};

#endif
