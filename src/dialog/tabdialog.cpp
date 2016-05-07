#include "tabdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
TabDialog::TabDialog(QWidget *parent, QString name, bool modal, Qt::WidgetAttribute f) :
    QDialog(parent/*, f*/),
    m_okButton(NULL), m_cancelButton(NULL), m_helpButton(NULL)
{
    if(f != Qt::WA_Disabled)
        setAttribute(f);
    setWindowTitle(name);
    setModal(modal);
    m_tabWidget = new QTabWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    m_buttonLayout = new QHBoxLayout();
    layout->addWidget(m_tabWidget);
    layout->addLayout(m_buttonLayout);
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChanged(int)));


}

void TabDialog::addTab(QWidget *tabWidget, QString name)
{
    m_tabWidget->addTab(tabWidget, name);
}
void TabDialog::insertTab(QWidget *tabWidget, QString name, int index)
{
    m_tabWidget->addTab(tabWidget, name);
    m_tabWidget->insertTab(index, tabWidget,name);
}

void TabDialog::setTabEnabled(QWidget *w, bool isEnabled)
{
    m_tabWidget->setTabEnabled(m_tabWidget->indexOf(w), isEnabled);
}

void TabDialog::onCurrentTabChanged(int i)
{
    emit currentChanged(m_tabWidget->widget(i));
}
void TabDialog::removePage(QWidget *page)
{
    m_tabWidget->removeTab(m_tabWidget->indexOf(page));
}

void TabDialog::setOkButton(QString name)
{
    if(name.isEmpty()){
        if(m_okButton)
        {
            delete m_okButton;
            m_okButton = NULL;
        }
        return;
    }
    if(m_okButton)
        return;
    m_okButton = new QPushButton(name,this);
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    m_buttonLayout->addWidget(m_okButton);
}

void TabDialog::setCancelButton(QString name)
{
    if(name.isEmpty()){
        if(m_cancelButton)
        {
            delete m_cancelButton;
            m_cancelButton = NULL;
        }
        return;
    }
    if(m_cancelButton)
        return;
    m_cancelButton = new QPushButton(name,this);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    m_buttonLayout->addWidget(m_cancelButton);
}

void TabDialog::setHelpButton(QString name)
{
    if(name.isEmpty()){
        if(m_helpButton)
        {
            delete m_helpButton;
            m_helpButton = NULL;
        }
        return;
    }
    if(m_helpButton)
        return;
    m_helpButton = new QPushButton(name,this);
    connect(m_helpButton, SIGNAL(clicked()), this, SIGNAL(helpButtonPressed()));
    m_buttonLayout->addWidget(m_helpButton);

}

void TabDialog::showPage(QWidget *page)
{
    m_tabWidget->setCurrentWidget(page);
}

void TabDialog::setCaption(QString cap)
{
    setWindowTitle(cap);
}

