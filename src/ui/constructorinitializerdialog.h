#ifndef CONSTRUCTORINITIALIZERDIALOG_H
#define CONSTRUCTORINITIALIZERDIALOG_H

#include <QDialog>
//#include "EdgeMenuDialog.h"
#include "dialog/edgemenudialogqt4.h"
//#include "dialogsubclass.h"
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
