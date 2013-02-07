// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko  .
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
#ifndef OPERATIONWIDGETCPP_H
#define OPERATIONWIDGETCPP_H

#include <QWidget>

namespace Ui
{
class OperationWidgetCpp;
}

class OperationWidgetCpp : public QWidget
{
    Q_OBJECT

public:
    explicit OperationWidgetCpp(QWidget * parent = 0);
    ~OperationWidgetCpp();
    Ui::OperationWidgetCpp * ui;
private:

};

#endif // OPERATIONWIDGETCPP_H
