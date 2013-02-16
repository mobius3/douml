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
#include "Factories/EdgeToolBarCreation.h"
#include "CustomWidgets/MultiPurposeDragArea.h"
#include "CustomWidgets/EdgeMenuToolBar.h"
#include <QPushButton>
#include <QIcon>
#include <QHBoxLayout>
#include <QLabel>
#include <QAction>
#include <QFileInfo>

static int defaultButtonSize = 15;
EdgeMenuToolBar * CreateLimitedDialogMenu()
{
    EdgeMenuToolBar * toolbar = new EdgeMenuToolBar();
    toolbar->setAttribute(Qt::WA_ShowWithoutActivating);
    QAction * clipboardAction = new QAction(toolbar);
    clipboardAction->setText("Clip...");
    clipboardAction->setName("Clipboard");

    MultiPurposeDragArea * dragArea = new MultiPurposeDragArea();
    dragArea->setName("DragArea");
    dragArea->setBaseSize(defaultButtonSize, defaultButtonSize);
    dragArea->setMinimumHeight(defaultButtonSize);
    dragArea->setMinimumWidth(defaultButtonSize);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    QLabel * label = new QLabel();

    label->setPixmap(QIcon(":/root/icons/mouse_control.png").pixmap());
    layout->addWidget(label);
    dragArea->setLayout(layout);

    QPushButton * okayElement = new QPushButton();
    okayElement->setIcon(QIcon(":/root/icons/accept.png"));
    okayElement->setName("OkayElement");
    okayElement->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    okayElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    QPushButton * cancelElement = new QPushButton();
    cancelElement->setIcon(QIcon(":/root/icons/reject.png"));
    cancelElement->setName("CancelElement");
    okayElement->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    cancelElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    toolbar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    toolbar->setMinimumHeight(defaultButtonSize);
    toolbar->setMinimumWidth(defaultButtonSize);
    toolbar->resize(toolbar->sizeHint());
    toolbar->setWindowFlags(Qt::FramelessWindowHint);

    toolbar->addWidget(dragArea);
    toolbar->addWidget(cancelElement);
    toolbar->addAction(clipboardAction);
    toolbar->addWidget(okayElement);


    return toolbar;
}

EdgeMenuToolBar * CreateClassDialogMenu()
{
    EdgeMenuToolBar * toolbar = new EdgeMenuToolBar();
    //toolbar->setWindowFlags(Qt::Tool);

    QAction * clipboardAction = new QAction(toolbar);
    clipboardAction->setName("Clipboard");
    clipboardAction->setText("Clip...");

    MultiPurposeDragArea * dragArea = new MultiPurposeDragArea();
    dragArea->setName("DragArea");
    dragArea->setBaseSize(defaultButtonSize, defaultButtonSize);
    dragArea->setMinimumHeight(defaultButtonSize);
    dragArea->setMinimumWidth(defaultButtonSize);
    QHBoxLayout * layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    QLabel * label = new QLabel();
    label->setPixmap(QIcon(":/root/icons/mouse_control.png").pixmap());
    layout->addWidget(label);
    dragArea->setLayout(layout);

//    QFileInfo f(":/root/icons/mouse_control.png");
//    bool exists = f.exists();

    QPushButton * okayElement = new QPushButton();
    okayElement->setIcon(QIcon(":/root/icons/accept.png"));
    okayElement->setName("OkayElement");
    okayElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    QPushButton * nextElement = new QPushButton();
    nextElement->setIcon(QIcon(":/root/icons/up.png"));
    nextElement->setName("NextElement");
    nextElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    QPushButton * previousElement = new QPushButton();
    previousElement->setIcon(QIcon(":/root/icons/down.png"));
    previousElement->setName("PreviousElement");
    previousElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    QPushButton * cancelElement = new QPushButton();
    cancelElement->setIcon(QIcon(":/root/icons/reject.png"));
    cancelElement->setName("CancelElement");
    cancelElement->setBaseSize(defaultButtonSize, defaultButtonSize);

    toolbar->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    toolbar->setMinimumHeight(defaultButtonSize);
    toolbar->setMinimumWidth(defaultButtonSize);
    toolbar->resize(toolbar->sizeHint());
    toolbar->setWindowFlags(Qt::FramelessWindowHint);

    toolbar->addWidget(dragArea);

    toolbar->addWidget(cancelElement);
    toolbar->addWidget(nextElement);
    toolbar->addWidget(previousElement);
    toolbar->addAction(clipboardAction);
    toolbar->addWidget(okayElement);
    return toolbar;
}

