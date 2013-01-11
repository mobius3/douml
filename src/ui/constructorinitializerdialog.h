#ifndef CONSTRUCTORINITIALIZERDIALOG_H
#define CONSTRUCTORINITIALIZERDIALOG_H

#include <QDialog>
class OperationData;
namespace Ui {
class ConstructorInitializerDialog;
}

class ConstructorInitializerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConstructorInitializerDialog(QWidget *parent = 0);
    ~ConstructorInitializerDialog();
    Ui::ConstructorInitializerDialog *ui;
    void Init(OperationData*);

    void reject() override;
    void accept() override;
private:
    OperationData* oper = nullptr;
    QString initializerCopy;
    QString definitionCopy;

    void RegenerateConstructor();
public slots:
    void OnInitializerChanged();
    

};

#endif // CONSTRUCTORINITIALIZERDIALOG_H
