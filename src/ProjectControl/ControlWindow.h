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

#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <q3mainwindow.h>
#include <qstringlist.h>

class BrowserView;
class BrowserNode;
class QDir;

// singleton

class ControlWindow : public Q3MainWindow
{
    Q_OBJECT

public:
    ControlWindow(QDir & homeDir);
    virtual ~ControlWindow();

protected:
    static ControlWindow * the;

    BrowserView * browser;
    QStringList historic;

    void load(QString path);
    void show_identity();

private slots:
    void load();
    void quit();
    void browser_search();
    void historicActivated(int id);
    void change_user();


    void motif_style();
    void motifplus_style();
    void windows_style();

    void about();
    void aboutQt();
};

#endif
