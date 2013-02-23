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
#include <algorithm>
#include <boost/bind.hpp>
//#include <boost/bind/placeholders.hpp>
//#include <boost/mpl/placeholders.hpp>
static Builtin rowTemporary;

//static bool SortBuiltinAscending(void* val1, void* val2)
//{
//    return static_cast<Builtin*>(val1)->uml < static_cast<Builtin*>(val2)->uml;
//}
//static bool SortBuiltinDescending(void* val1, void* val2)
//{
//    return static_cast<Builtin*>(val1)->uml < static_cast<Builtin*>(val2)->uml;
//}

static void InsertRow(QList<Builtin>& builtins, const Builtin& newRowValue, const Builtin& currentRowValue, AdaptingTableModel* model, QSharedPointer<TableDataInterface> interface, ERowInsertMode insertMode)
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
    model->SetInterface(interface);
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
            QMessageBox::critical(0, tr("Error"), "Uml/Cpp/Java/Idl fields cannot be empty");
            return false;
        }
        QList<Builtin>& builtins =  GenerationSettings::builtins;
        std::function<bool(const Builtin&)> func = [&](const Builtin& val1){return val1.uml == value.uml;};
        int count = std::count_if(builtins.begin(), builtins.end(), func);
        if(count > 1)
        {
            QMessageBox::critical(0, tr("Error"), "Duplicate Uml entries are not allowed");
            return false;
        }
        if(!value.cpp_in.contains("${type}") ||
                !value.cpp_in.contains("${type}") ||
                !value.cpp_inout.contains("${type}") ||
                !value.cpp_out.contains("${type}") ||
                !value.cpp_return.contains("${type}"))
        {
            QMessageBox::critical(0, tr("Error"), "Cpp parameter controls must contain ${type}");
            return false;
        }
    }
    return true;
}

void BuiltinTable::RollBack()
{
    GenerationSettings::builtins = rollbackBuiltins;
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
    holder->SetColumns(QStringList() << "Uml" << "Cpp" << "Java" << "Idl" << "cpp_in" << "cpp_out" << "cpp_inout" << "cpp_return" << "do");

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
}

void BuiltinTable::InitInterface()
{
    QHBoxLayout* layControls = new QHBoxLayout;
    pbAddNewType = new QPushButton(QIcon(":/root/icons/bullet_add.png"), "Add type");
    lblVisibility = new QLabel("Language visibility:");
    //lblSort = new QLabel("Sort order:");
    chkCpp = new QCheckBox("C++");
    chkCpp->setChecked(true);
    chkJava = new QCheckBox("Java");
    chkJava->setChecked(true);
    chkIdl = new QCheckBox("Idl");
    chkIdl->setChecked(true);
    lblSearch = new QLabel("Search:");
    leSearch = new QLineEdit();
//    cbSort = new QComboBox();
//    cbSort->addItem(tr("None"));
//    cbSort->addItem(tr("Ascending"));
//    cbSort->addItem(tr("Descending"));
//    cbSort->setCurrentIndex(0);
    layControls->addWidget(pbAddNewType);
    //layControls->addWidget(lblSort);
    //layControls->addWidget(cbSort);
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
        QAction* actInsertNewBefore = menuRow->addAction("Insert row before", this, SLOT(OnInsertNewRow()));
        actInsertNewBefore->setData("before");
        QAction* actInsertNewAfter = menuRow->addAction("Insert row after", this, SLOT(OnInsertNewRow()));
        actInsertNewAfter->setData("after");
        menuRow->addSeparator();
        menuRow->addAction("Copy row", this, SLOT(OnCopyRow()));
        menuRow->addAction("Paste row", this, SLOT(OnPasteRow()));
//        actPasteRowBefore->setData("before");
//        QAction* actPasteRowAfter = menuRow->addAction("Paste row after", this, SLOT(OnPasteRow()));
//        actPasteRowAfter->setData("after");
        menuRow->addAction("Cut row", this, SLOT(OnCutRow()));
        menuRow->addSeparator();
        menuRow->addAction("Delete row", this, SLOT(OnDeleteRow()));
    }
}

void BuiltinTable::CreateConnections()
{
    connect(types_table, SIGNAL(clicked(QModelIndex)), this, SLOT(OnCallRowMenu(QModelIndex)));
    connect(chkCpp, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(chkIdl, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(chkJava, SIGNAL(clicked()),this, SLOT(OnSetParameterVisibility()));
    connect(leSearch, SIGNAL(textEdited(QString)), this, SLOT(OnFilterTable(QString)));

}

void BuiltinTable::OnAddNewType()
{
}

void BuiltinTable::OnCppVisibilityToggled(bool)
{
}

void BuiltinTable::OnJavaVisibilityToggled(bool)
{
}

void BuiltinTable::OnIdlVisibilityToggled(bool)
{
}

void BuiltinTable::OnInsertNewRow()
{
    QAction* senderAction = dynamic_cast<QAction*>(sender());
    //TableDataInterface* iFace = static_cast<TableDataInterface*>(types_table->currentIndex().internalPointer());
    QModelIndex current = types_table->selectionModel()->currentIndex();
    current = sortModel->mapToSource(current);
    Builtin* holderPtr = static_cast<Builtin*>(current.internalPointer());

    if(senderAction->data().toString() == "before")
        InsertRow(GenerationSettings::builtins, Builtin(), *holderPtr, typetableModel, typetableInterface, ERowInsertMode::before_current);
    else
        InsertRow(GenerationSettings::builtins, Builtin(), *holderPtr, typetableModel, typetableInterface, ERowInsertMode::after_current);

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
    //typetableInterface->
    //Builtin* holderPtr = static_cast<Builtin*>(current.internalPointer());

    //std::function<bool(Builtin)> func = [&](const Builtin& val1){return val1 == *holderPtr;};
    //it = std::find_if(builtins.begin(),builtins.end(), std::bind(func, std::placeholders::_1));


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
        return QVariant(QString("   "));
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
    sortModel->setFilterRegExp(val);
    sortModel->setDynamicSortFilter(true);
}



