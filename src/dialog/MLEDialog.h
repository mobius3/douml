// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
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
// e-mail : enmarantispam@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************

#ifndef MLEDIALOG_H
#define MLEDIALOG_H

#include <qdialog.h>

class MultiLineEdit;
class QPushButton;

class MLEDialog : public QDialog
{
    Q_OBJECT

protected:
    MultiLineEdit * e;
    QPushButton * ok;
    QPushButton * cancel;

public:
    MLEDialog(QString t, bool buttons);
    virtual ~MLEDialog();

    QString text();

public:
    static void get(QString & t, const QPoint & p, QSize & sz);
};

#endif

