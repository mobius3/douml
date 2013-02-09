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
#ifndef EDGEMENUTOOLBAR_H
#define EDGEMENUTOOLBAR_H
#include <QToolBar>
#include <QTimer>
#include <QMenu>
#include "CustomWidgets/MultiPurposeDragArea.h"
class EdgeMenuDialog;
class EdgeMenuToolBar : public QToolBar
{
    Q_OBJECT

public:
    EdgeMenuToolBar(QWidget * _parent = 0);
    ~EdgeMenuToolBar();
    void SetRelativeOrientation(int);
    void SetDialog(EdgeMenuDialog *);
protected:
    //! called on window show()
    void leaveEvent(QEvent * event);
    void enterEvent(QEvent * event);

    void focusOutEvent(QFocusEvent *) override;
private:

    void IntitiateMove(QPoint);
    void IntitiateResize(QPoint);
    void MoveThis(QPoint, QPoint);
    void FillClipboardMenu(int);
    QPoint modificationOrigin;
    QPoint toolbarOrigin;
    EWidgetModificationMode modificationMode;
    QTimer decayTimer;
    int relativeOrientation;
    QMenu * clipboardMenu;
    int lastClipboardItemShown;
    int clipboardListSize;
    EdgeMenuDialog * linkedDialog = 0;

public slots:
    virtual void OnInitiateMove(QPoint);
    virtual void OnInitiateResize(QPoint);
    virtual void OnNewCoordinatesReceived(QPoint);
    virtual void OnEndResize();
    virtual void OnEndMove();
    virtual void OnClipboardRequested();
    virtual void OnMoreClipboardRequested();
    virtual void OnLessClipboardRequested();
    virtual void OnPutIntoClipboardRequested();
    virtual void OnDialogLostFocus();
    virtual void OnMenuHideRequested();
    virtual void OnMenuRepositionRequested(const QPoint &);

signals:
    void putIntoClipboard(QString);

};


#endif // EDGEMENUTOOLBAR_H
