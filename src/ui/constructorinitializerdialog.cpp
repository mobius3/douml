#include "constructorinitializerdialog.h"
#include "ui_constructorinitializerdialog.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "misc/TypeIdentifier.h"
#include "tagmanagement/cpptagmanagement.h"
//#include "edge
ConstructorInitializerDialog::ConstructorInitializerDialog(QWidget *parent) :
    EdgeMenuDialogQt4(parent),
    ui(new Ui::ConstructorInitializerDialog)
{
    ui->setupUi(this);
    connect(this->ui->pbOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this->ui->pbCancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->resize(sizeHint());
    QApplication::processEvents();
}

ConstructorInitializerDialog::~ConstructorInitializerDialog()
{
    delete ui;
}

void ConstructorInitializerDialog::Init(OperationData * _oper)
{
    this->setWindowTitle(tr("Constructor-initializer setup"));
    oper = _oper;
    QString constructorPrototype = ui->edConstructorPrototype->toPlainText();
    if(!constructorPrototype.contains("@{constructor-initializer}"))
        ui->edConstructorPrototype->setText(constructorPrototype.replace("${volatile}", "@{constructor-initializer}${volatile}"));
    initializerCopy = QString(oper->get_browser_node()->get_value("constructor-initializer"));
    definitionCopy = oper->get_cppdef();
    oper->set_cppdef(ui->edConstructorPrototype->text());
    connect(ui->edInitializer,SIGNAL(textChanged()),this, SLOT(OnInitializerChanged()));
    oper->get_browser_node()->set_value("constructor-initializer", ui->edInitializer->toPlainText());
    RegenerateConstructor();

}

void ConstructorInitializerDialog::reject()
{
   oper->get_browser_node()->set_value("constructor-initializer", initializerCopy);
   oper->set_cppdef(definitionCopy);
   toolbar->setParent(0);
   toolbar->hide();
   QDialog::reject();
}

void ConstructorInitializerDialog::accept()
{
    toolbar->setParent(0);
    toolbar->hide();
    QDialog::accept();
}

uint ConstructorInitializerDialog::TypeID()
{
    return TypeIdentifier<ConstructorInitializerDialog>::id();
}

void ConstructorInitializerDialog::RegenerateConstructor()
{
    QString constructorActual = TagManagers::Cpp::updated_def(oper);
    ui->edActualConstructor->setText(constructorActual);
}

void ConstructorInitializerDialog::OnInitializerChanged()
{
    oper->get_browser_node()->set_value("constructor-initializer", ui->edInitializer->toPlainText());
    RegenerateConstructor();
}
