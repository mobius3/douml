#ifndef GENERATIONSETTINGSBUILTINTABLE_H
#define GENERATIONSETTINGSBUILTINTABLE_H
#include <QWidget>
class QTableView;
#include "Libs/L_UniversalModels/include/ItemController.h"
#include "Libs/L_UniversalModels/include/TableDataInterface.h"
#include "Libs/L_UniversalModels/include/TableDataListHolder.h"
#include "GenerationSettings.h"

class AdaptingTableModel;
//class Builtin;
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
    void OnSetParameterVisibility();
    void OnFilterTable(QString);

};

#endif // GENERATIONSETTINGSBUILTINTABLE_H
