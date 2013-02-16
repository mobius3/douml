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
#ifndef CONSTRUCTORINITIALIZERDIALOG_H
#define CONSTRUCTORINITIALIZERDIALOG_H

#include <QDialog>
#include "dialog/edgemenudialogqt4.h"
class OperationData;
namespace Ui {
class ConstructorInitializerDialog;
}

class ConstructorInitializerDialog : public EdgeMenuDialogQt4
{
    Q_OBJECT
    
public:
    explicit ConstructorInitializerDialog(QWidget *parent = 0);
    ~ConstructorInitializerDialog();
    Ui::ConstructorInitializerDialog *ui;
    void Init(OperationData*);

    void reject() override;
    void accept() override;
    //! return unique TypeId associated with each classs
    //! crc on PRETTY_FUNCTION is basically used to create one
    virtual uint TypeID() ;
private:
    OperationData* oper = nullptr;
    QString initializerCopy;
    QString definitionCopy;

    void RegenerateConstructor();
public slots:
    void OnInitializerChanged();
    

};

#endif // CONSTRUCTORINITIALIZERDIALOG_H
