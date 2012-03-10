// *************************************************************************
//
// Copyright 2012-2012 Nikolai Marchenko.
//
// This file is part of the BreezeUML Uml Toolkit.
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
//
// *************************************************************************
#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>
#include <functional>
#include <map>
#include <QMap>

#include "misc/SingletonHolder.h"


//#include <pair>
class EdgeMenuDialog;

struct Orientationvariables
{
    int orientation;
    //std::map<std::pair<int,QString>, QString> iconNames;
};

typedef std::function<QToolBar*()>  ToolbarFactory;
typedef std::function<void(EdgeMenuDialog*,QToolBar*)>  ConnectionFunctor;

void ConnectToLimitedtDialog(EdgeMenuDialog* dialog, QToolBar* toolbar);
void ConnectToClassDialog(EdgeMenuDialog* dialog, QToolBar* toolbar);

QToolBar* CreateClassDialogMenu();
QToolBar* CreateLimitedDialogMenu();

class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();

    void AddFactory(uint, ToolbarFactory);
    void AddConnectionFunctor(uint, ConnectionFunctor);
    void SpawnEdgeMenu(uint, EdgeMenuDialog*,  QPoint);
public slots:
    void OnEdgeMenuRequested(uint classID);

private :
    QMap<uint, ToolbarFactory > factories;
    QMap<uint, ConnectionFunctor > signalFunctors;
    QMap<uint, QToolBar*> createdToolbars;
    QMap<int, Orientationvariables> orientationSwitch;
    void SpawnEdgeMenu(uint, EdgeMenuDialog*);

};
BIND_TO_SELF_SINGLE(EdgeMenuFactory);


#endif // EDGEMENUFACTORY_H
