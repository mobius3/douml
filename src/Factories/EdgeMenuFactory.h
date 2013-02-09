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
#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>
#include <functional>
#include <map>
#include <QMap>

#include "misc/SingletonHolder.h"

class EdgeMenuDialog;
class EdgeMenuDialogBase;
class EdgeMenuDialogQt4;
class EdgeMenuToolBar;

struct Orientationvariables {
    int orientation;
    //std::map<std::pair<int,QString>, QString> iconNames;
};

typedef std::function<EdgeMenuToolBar*()>  ToolbarFactory;
typedef std::function<void(EdgeMenuDialog *, EdgeMenuToolBar *)>  ConnectionFunctor;
typedef std::function<void(EdgeMenuDialogQt4 *, EdgeMenuToolBar *)>  ConnectionFunctorQt4;

void ConnectToLimitedtDialog(EdgeMenuDialog * dialog, EdgeMenuToolBar * toolbar);
void ConnectToClassDialog(EdgeMenuDialog * dialog, EdgeMenuToolBar * toolbar);

class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();

    void AddFactory(uint, ToolbarFactory);
    void AddConnectionFunctor(uint, ConnectionFunctor);
    void AddConnectionFunctorQt4(uint, ConnectionFunctorQt4);
    void SpawnEdgeMenu(uint, EdgeMenuDialogBase*);
public slots:
    void OnEdgeMenuRequested(uint classID);

private :
    QMap<uint, ToolbarFactory > factories;
    QMap<uint, ConnectionFunctor > signalFunctors;
    QMap<uint, ConnectionFunctorQt4 > signalFunctorsQt4;
    QMap<uint, EdgeMenuToolBar *> createdToolbars;
    QMap<int, Orientationvariables> orientationSwitch;
};
BIND_TO_SELF_SINGLE(EdgeMenuFactory);
#endif // EDGEMENUFACTORY_H
