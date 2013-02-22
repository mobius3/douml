#include "GenerationSettingsBuiltinTable.h"
#include "GenerationSettings.h"
#include "Libs/L_UniversalModels/include/AdaptingTableModel.h"
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QMenu>
#include <algorithm>
static Builtin rowTemporary;

static void InsertRow(QList<Builtin>& builtins, Builtin newRowValue, const Builtin& currentRowValue, AdaptingTableModel* model, QSharedPointer<TableDataInterface> interface, ERowInsertMode insertMode)
{
    TableDataListHolder<Builtin> * holderPtr = static_cast<TableDataListHolder<Builtin>* >(interface.data());

    QList<Builtin>::Iterator it;
    if(insertMode == ERowInsertMode::before_current || insertMode == ERowInsertMode::after_current)
    {
        it = std::find(builtins.begin(),builtins.end(), currentRowValue);
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
    CreateConnections();

}

void BuiltinTable::TableSetup()
{
    holder = new TableDataListHolder<Builtin>();

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

    QSortFilterProxyModel* sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(typetableModel);
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
    chkCpp = new QCheckBox("C++");
    chkJava = new QCheckBox("Java");
    chkIdl = new QCheckBox("Idl");
    layControls->addWidget(pbAddNewType);
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
        QAction* actPasteRowBefore = menuRow->addAction("Paste row before", this, SLOT(OnPasteRow()));
        actPasteRowBefore->setData("before");
        QAction* actPasteRowAfter = menuRow->addAction("Paste row after", this, SLOT(OnPasteRow()));
        actPasteRowAfter->setData("after");
        menuRow->addAction("Cut row", this, SLOT(OnCutRow()));
        menuRow->addSeparator();
        menuRow->addAction("Delete row", this, SLOT(OnDeleteRow()));
    }
}

void BuiltinTable::CreateConnections()
{
    connect(types_table, SIGNAL(clicked(QModelIndex)), this, SLOT(OnCallRowMenu(QModelIndex)));
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
    TableDataInterface* iFace = static_cast<TableDataInterface*>(types_table->currentIndex().internalPointer());
    Builtin* holderPtr = static_cast<Builtin*>(iFace);
    if(senderAction->data().toString() == "before")
        InsertRow(GenerationSettings::builtins, Builtin(), *holderPtr, typetableModel, typetableInterface, ERowInsertMode::before_current);
    else
        InsertRow(GenerationSettings::builtins, Builtin(), *holderPtr, typetableModel, typetableInterface, ERowInsertMode::after_current);

}

void BuiltinTable::OnPasteRow()
{
}

void BuiltinTable::OnDeleteRow()
{
}

void BuiltinTable::OnCopyRow()
{
}

void BuiltinTable::OnCutRow()
{
}

#define ADD_STRING_GETSET(X,Y,Z)  \
X->AddGetter(QPair<int,int>(Y,0), \
[] (const Builtin* data) \
{ \
    if(data) \
        return QVariant(data->Z); \
    else \
        return QVariant(); \
} \
); \
X->AddSetter(QPair<int,int>(Y,0), \
[] (Builtin* data, QVariant value) \
{ \
    if(data) \
        data->Z = value.toString(); \
} \
); \

void BuiltinTable::SetupAccess()
{
    ADD_STRING_GETSET(holder, 0, uml);
    ADD_STRING_GETSET(holder, 1, cpp);
    ADD_STRING_GETSET(holder, 2, java);
    ADD_STRING_GETSET(holder, 3, idl);
    ADD_STRING_GETSET(holder, 4, cpp_in);
    ADD_STRING_GETSET(holder, 5, cpp_out);
    ADD_STRING_GETSET(holder, 6, cpp_inout);
    ADD_STRING_GETSET(holder, 7, cpp_return);
    holder->AddGetter(QPair<int,int>(8,0),
    [] (const Builtin* )
    {
        return QVariant(QString("   "));
    });
}


void BuiltinTable::OnCallRowMenu(const QModelIndex & index)
{
    if(index.column() == 8)
        menuRow->popup(QCursor::pos());
}



