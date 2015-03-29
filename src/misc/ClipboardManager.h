// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko.
//
// This file is part of the Douml Uml Toolkit.
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
//
// *************************************************************************
#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QMenu>
#include <QStringList>
#include "misc/SingletonHolder.h"

class ClipboardManager : public QObject
{
    Q_OBJECT
public:
    ClipboardManager(QObject * _parent = 0);
    ~ClipboardManager();
    QStringList GetStrings();
    QMenu* GetMenuInstance(int base = 0, QMenu * existingMenu = nullptr);
public slots:
    virtual void OnClipboardUpdate();
    virtual void OnPutItemIntoClipboard(QString);

    virtual void OnPutItemIntoClipboardRequested();
    virtual void OnClipboardRequested();
    virtual void OnMoreClipboardRequested();
    virtual void OnLessClipboardRequested();

private:
    void FillClipboardMenu(QMenu* clipboardMenu, int base);
    QStringList strings;
    QMenu* clipboardMenu = nullptr;

    int lastClipboardItemShown = 0;
    int clipboardListSize = 10;

};
BIND_TO_SELF_SINGLE(ClipboardManager);
#endif // CLIPBOARDMANAGER_H
