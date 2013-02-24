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
#ifndef GENERATIONSETTINGSBUILTINTABLE_H
#define GENERATIONSETTINGSBUILTINTABLE_H
#include <QWidget>
#include "Libs/L_UniversalModels/include/TableDataInterface.h"
#include "Libs/L_UniversalModels/include/TableDataListHolder.h"
#include "GenerationSettings.h"

class QTableView;
class AdaptingTableModel;
class QCheckBox;
class QPushButton;
class QLabel;
class QMenu;
class QComboBox;
class QLineEdit;
class QSortFilterProxyModel;
enum class ERowInsertMode
{
    before_first,
    before_current,
    after_last,
    after_current
};
class BuiltinTable : public QWidget
{
    Q_OBJECT
public:
    BuiltinTable(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~BuiltinTable();
    void Init();
    bool ValidateTypes();
    void RollBack();
    QList<Builtin> GetBuiltins();
    QSize GetOptimalSize();

private:
    void SetupAccess();
    void TableSetup();
    void InitInterface();

    void CreateRowMenu();
    void CreateConnections();

    QTableView* types_table = nullptr;
    QSortFilterProxyModel* sortModel;
    AdaptingTableModel* typetableModel = nullptr;
    QSharedPointer<TableDataInterface> typetableInterface;
    TableDataListHolder<Builtin>* holder = nullptr;
    QCheckBox* chkCpp = nullptr;
    QCheckBox* chkJava = nullptr;
    QCheckBox* chkIdl = nullptr;
    QComboBox* cbSort = nullptr;
    QLabel* lblVisibility = nullptr;
    QLabel* lblSort = nullptr;
    QLabel* lblSearch = nullptr;
    QPushButton* pbAddNewType = nullptr;
    QLineEdit* leSearch = nullptr;
    QMenu* menuRow = nullptr;
    QList<Builtin> rollbackBuiltins;
public slots:
    void OnInsertNewRow();
    void OnPasteRow();
    void OnDeleteRow();
    void OnCopyRow();
    void OnCutRow();
    void OnCallRowMenu(const QModelIndex&);
    void OnSetParameterVisibility();
    void OnFilterTable(QString);

};

#endif // GENERATIONSETTINGSBUILTINTABLE_H
