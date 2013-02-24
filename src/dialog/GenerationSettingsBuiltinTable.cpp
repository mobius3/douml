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
#include "GenerationSettingsBuiltinTable.h"
#include "GenerationSettings.h"
#include "Libs/L_UniversalModels/include/AdaptingTableModel.h"
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QMenu>
#include <QLineEdit>
#include <QMessageBox>
#include <QApplication>
#include <QHeaderView>
#include <algorithm>
static Builtin rowTemporary;
static void InsertRow(QList<Builtin>& builtins, const Builtin& newRowValue, const Builtin& currentRowValue, QSharedPointer<TableDataInterface> interface, ERowInsertMode insertMode)
{
    TableDataListHolder<Builtin>* holder = static_cast<TableDataListHolder<Builtin>*>(interface.data());
    QList<Builtin>::Iterator it;
    if(insertMode == ERowInsertMode::before_current || insertMode == ERowInsertMode::after_current)
    {
        using std::placeholders::_1;
        std::function<bool(Builtin)> func = [&](const Builtin& val1){return val1 == currentRowValue;};
        it = std::find_if(builtins.begin(),builtins.end(), std::bind(func, std::placeholders::_1));
        if(insertMode == ERowInsertMode::after_current)
            it++;
    }
    else if(insertMode == ERowInsertMode::before_first)
    {
        it = builtins.begin();
    }
    else
    {
        it = builtins.end() - 1;
    }
    builtins.insert(it,newRowValue);
    QList<Builtin*> newBuiltins;
    for(int i(0); i < builtins.size(); i++)
    {
        newBuiltins.append(&builtins[i]);
    }
    holder->SetData(newBuiltins);
}


BuiltinTable::BuiltinTable(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
}

BuiltinTable::~BuiltinTable()
{
}

void BuiltinTable::Init()
{
    InitInterface();
    CreateRowMenu();
    TableSetup();
    OnSetParameterVisibility();
    CreateConnections();
    sortModel->sort(0, Qt::AscendingOrder);

}

bool BuiltinTable::ValidateTypes()
{
    for(Builtin& value : GenerationSettings::builtins)
    {
        if(value.uml.trimmed().isEmpty() ||
                value.cpp.trimmed().isEmpty() ||
                value.java.trimmed().isEmpty() ||
                value.idl.trimmed().isEmpty() )
        {
            QMessageBox::critical(0, tr("Error"), tr("Uml/Cpp/Java/Idl fields cannot be empty"));
            return false;
        }
        QList<Builtin>& builtins =  GenerationSettings::builtins;
        std::function<bool(const Builtin&)> func = [&](const Builtin& val1){return val1.uml == value.uml;};
        int count = std::count_if(builtins.begin(), builtins.end(), func);
        if(count > 1)
        {
            QMessageBox::critical(0, tr("Error"), tr("Duplicate Uml entries are not allowed"));
            return false;
        }
        if(!value.cpp_in.contains("${type}") ||
                !value.cpp_in.contains("${type}") ||
                !value.cpp_inout.contains("${type}") ||
                !value.cpp_out.contains("${type}") ||
                !value.cpp_return.contains("${type}"))
        {
            QMessageBox::critical(0, tr("Error"), tr("Cpp parameter controls must contain ${type}"));
            return false;
        }
    }
    return true;
}

void BuiltinTable::RollBack()
{
    GenerationSettings::builtins = rollbackBuiltins;
}

QList<Builtin> BuiltinTable::GetBuiltins()
{
    QList<Builtin> result;
    QList<Builtin*> builtins = holder->GetData();
    for(Builtin* builtin : builtins)
    {
        if(builtin)
            result.append(*builtin);
    }
    return result;
}

QSize BuiltinTable::GetOptimalSize()
{
    QRect rect = types_table->geometry();
    int horizontalWidgth = 0;
    for(int i(0); i < types_table->horizontalHeader()->count(); i++)
    {
        if(!types_table->horizontalHeader()->isSectionHidden(i))
            horizontalWidgth+= types_table->horizontalHeader()->sectionSize(i);
    }
    rect.setWidth(horizontalWidgth);
    return QSize(rect.width()+45, rect.height());
}

void BuiltinTable::TableSetup()
{
    holder = new TableDataListHolder<Builtin>();
    rollbackBuiltins = GenerationSettings::builtins;
    QList<Builtin*> builtInList;
    for(int i(0); i < GenerationSettings::nbuiltins; i++)
    {
        builtInList.append(&GenerationSettings::builtins[i]);
    }

    typetableModel = new AdaptingTableModel();

    SetupAccess();

    holder->SetData(builtInList);
    holder->SetColumns(QStringList() << "Uml" << "Cpp" << "Java" << "Idl" << "cpp_in" << "cpp_out" << "cpp_inout" << "cpp_return" << tr("do"));

    typetableInterface = QSharedPointer<TableDataInterface>(dynamic_cast<TableDataInterface*>(holder));

    typetableModel->SetInterface(typetableInterface);

    sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(typetableModel);
    sortModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    types_table->setModel(sortModel);

    types_table->setAlternatingRowColors(true);
    types_table->setSortingEnabled(true);
    types_table->resizeColumnToContents(0);
    types_table->resizeColumnToContents(8);
    types_table->resizeRowsToContents();
}

void BuiltinTable::InitInterface()
{
    QHBoxLayout* layControls = new QHBoxLayout;
    pbAddNewType = new QPushButton(QIcon(":/root/icons/bullet_add.png"), tr("Add type"));
    lblVisibility = new QLabel(tr("Language visibility:"));
    chkCpp = new QCheckBox("C++");
    chkCpp->setChecked(true);
    chkJava = new QCheckBox("Java");
    chkJava->setChecked(true);
    chkIdl = new QCheckBox("Idl");
    chkIdl->setChecked(true);
    lblSearch = new QLabel(tr("Search:"));
    leSearch = new QLineEdit();
    layControls->addWidget(pbAddNewType);
    layControls->addWidget(lblSearch);
    layControls->addWidget(leSearch);
    layControls->addWidget(lblVisibility);
    layControls->addWidget(chkCpp);
    layControls->addWidget(chkJava);
    layControls->addWidget(chkIdl);
    layControls->addStretch();

    QVBoxLayout* layMain = new QVBoxLayout;
    types_table = new QTableView();
    layMain->addLayout(layControls);
    layMain->addWidget(types_table);
    layMain->setContentsMargins(0,0,0,0);

    this->setLayout(layMain);


}

void BuiltinTable::CreateRowMenu()
{
    if(!menuRow)
    {
        menuRow = new QMenu();
        menuRow->addSeparator();
        menuRow->addAction(tr("Copy row"), this, SLOT(OnCopyRow()));
        menuRow->addAction(tr("Paste row"), this, SLOT(OnPasteRow()));
        menuRow->addAction(tr("Cut row"), this, SLOT(OnCutRow()));
        menuRow->addSeparator();
        menuRow->addAction(tr("Delete row"), this, SLOT(OnDeleteRow()));
    }
}

void BuiltinTable::CreateConnections()
{
    connect(types_table, SIGNAL(clicked(QModelIndex)), this, SLOT(OnCallRowMenu(QModelIndex)));
    connect(chkCpp, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(chkIdl, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(chkJava, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(leSearch, SIGNAL(textEdited(QString)), this, SLOT(OnFilterTable(QString)));
    connect(pbAddNewType, SIGNAL(clicked()),this, SLOT(OnInsertNewRow()));

}


void BuiltinTable::OnInsertNewRow()
{
    InsertRow(GenerationSettings::builtins, Builtin(), Builtin(), typetableInterface, ERowInsertMode::after_last);
}

void BuiltinTable::OnPasteRow()
{
    QModelIndex current = types_table->selectionModel()->currentIndex();
    current = sortModel->mapToSource(current);

    typetableModel->setData(current.sibling(current.row(),0), rowTemporary.uml, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),1), rowTemporary.cpp, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),2), rowTemporary.java, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),3), rowTemporary.idl, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),4), rowTemporary.cpp_in, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),5), rowTemporary.cpp_out, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),6), rowTemporary.cpp_inout, Qt::DisplayRole);
    typetableModel->setData(current.sibling(current.row(),7), rowTemporary.cpp_return, Qt::DisplayRole);
}

void BuiltinTable::OnDeleteRow()
{
    QModelIndex current = types_table->selectionModel()->currentIndex();
    current = sortModel->mapToSource(current);
    typetableModel->RemoveRow(current);
}

void BuiltinTable::OnCopyRow()
{
    QModelIndex current = types_table->selectionModel()->currentIndex();
    current = sortModel->mapToSource(current);
    Builtin* holderPtr = static_cast<Builtin*>(current.internalPointer());
    if(holderPtr)
        rowTemporary = *holderPtr;
}

void BuiltinTable::OnCutRow()
{
    OnCopyRow();
    OnDeleteRow();
}

#define ADD_STRING_GETSET(HOLDER,ROW,ROLE,PARAM)  \
HOLDER->AddGetter(QPair<int,int>(ROW,ROLE), \
[] (const Builtin* data) \
{ \
    if(data) \
        return QVariant(data->PARAM); \
    else \
        return QVariant(); \
} \
); \
HOLDER->AddSetter(QPair<int,int>(ROW,ROLE), \
[] (Builtin* data, QVariant value) \
{ \
    if(data) \
        data->PARAM = value.toString(); \
} \
); \

void BuiltinTable::SetupAccess()
{
    ADD_STRING_GETSET(holder, 0, 0, uml);
    ADD_STRING_GETSET(holder, 1, 0, cpp);
    ADD_STRING_GETSET(holder, 2, 0, java);
    ADD_STRING_GETSET(holder, 3, 0, idl);
    ADD_STRING_GETSET(holder, 4, 0, cpp_in);
    ADD_STRING_GETSET(holder, 5, 0, cpp_out);
    ADD_STRING_GETSET(holder, 6, 0, cpp_inout);
    ADD_STRING_GETSET(holder, 7, 0, cpp_return);

    ADD_STRING_GETSET(holder, 0, 2, uml);
    ADD_STRING_GETSET(holder, 1, 2, cpp);
    ADD_STRING_GETSET(holder, 2, 2, java);
    ADD_STRING_GETSET(holder, 3, 2, idl);
    ADD_STRING_GETSET(holder, 4, 2, cpp_in);
    ADD_STRING_GETSET(holder, 5, 2, cpp_out);
    ADD_STRING_GETSET(holder, 6, 2, cpp_inout);
    ADD_STRING_GETSET(holder, 7, 2, cpp_return);
    holder->AddGetter(QPair<int,int>(8,0),
    [] (const Builtin* )
    {
        return QVariant(QString(" "));
    });

    holder->AddFlagsFunctor(
                [](const QModelIndex& index)
    {
        if(index.column() == 8)
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        Qt::ItemFlags result;
        result |= Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        return result;
    }
    );
}

void BuiltinTable::OnCallRowMenu(const QModelIndex & index)
{
    if(index.column() == 8)
        menuRow->popup(QCursor::pos());
}

void BuiltinTable::OnSetParameterVisibility()
{
    types_table->setColumnHidden(1, !chkCpp->isChecked());
    types_table->setColumnHidden(2, !chkJava->isChecked());
    types_table->setColumnHidden(3, !chkIdl->isChecked());
}

void BuiltinTable::OnFilterTable(QString val)
{
    sortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    sortModel->setFilterRegExp(val);
}



