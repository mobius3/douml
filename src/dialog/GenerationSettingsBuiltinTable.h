#ifndef GENERATIONSETTINGSBUILTINTABLE_H
#define GENERATIONSETTINGSBUILTINTABLE_H
#include <QWidget>
class QTableView;
#include "Libs/L_UniversalModels/include/ItemController.h"
#include "Libs/L_UniversalModels/include/TableDataInterface.h"
#include "Libs/L_UniversalModels/include/TableDataListHolder.h"

class AdaptingTableModel;
class Builtin;
class QCheckBox;
class QPushButton;
class QLabel;
class QMenu;
class BuiltinTable : public QWidget
{
    Q_OBJECT
public:
    BuiltinTable(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~BuiltinTable();
    void Init();

private:
    void SetupAccess();
    void TableSetup();
    void InitInterface();
    void CreateRowMenu();
    void CreateConnections();

    QTableView* types_table = nullptr;
    AdaptingTableModel* typetableModel = nullptr;
    QSharedPointer<TableDataInterface> typetableInterface;
    TableDataListHolder<Builtin>* holder = nullptr;
    QCheckBox* chkCpp = nullptr;
    QCheckBox* chkJava = nullptr;
    QCheckBox* chkIdl = nullptr;
    QLabel* lblVisibility = nullptr;
    QPushButton* pbAddNewType = nullptr;
    QMenu* menuRow = nullptr;
public slots:
    void OnAddNewType();
    void OnCppVisibilityToggled(bool);
    void OnJavaVisibilityToggled(bool);
    void OnIdlVisibilityToggled(bool);

    void OnInsertNewRow();
    void OnPasteRow();
    void OnDeleteRow();
    void OnCopyRow();
    void OnCutRow();
    void OnCallRowMenu(const QModelIndex&);

};

#endif // GENERATIONSETTINGSBUILTINTABLE_H
