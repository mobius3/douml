#include "tabdialogwrapper.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
TabDialogWrapper::TabDialogWrapper(QWidget *parent, const char *name, bool modal, Qt::WidgetAttribute f) :
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


}

void TabDialogWrapper::addTab(QWidget *tabWidget, QString name)
{
    m_tabWidget->addTab(tabWidget, name);
}
void TabDialogWrapper::insertTab(QWidget *tabWidget, QString name, int index)
{
    m_tabWidget->addTab(tabWidget, name);
    m_tabWidget->insertTab(index, tabWidget,name);
}

void TabDialogWrapper::setTabEnabled(QWidget *w, bool isEnabled)
{
    m_tabWidget->setTabEnabled(m_tabWidget->indexOf(w), isEnabled);
}
void TabDialogWrapper::removePage(QWidget *page)
{
    m_tabWidget->removeTab(m_tabWidget->indexOf(page));
}

void TabDialogWrapper::setOkButton(QString name)
{
    if(m_okButton)
        return;
    m_okButton = new QPushButton(name,this);
    connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    m_buttonLayout->addWidget(m_okButton);
}

void TabDialogWrapper::setCancelButton(QString name)
{
    if(m_cancelButton)
        return;
    m_cancelButton = new QPushButton(name,this);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    m_buttonLayout->addWidget(m_cancelButton);
}

void TabDialogWrapper::setHelpButton(QString name)
{
    if(m_helpButton)
        return;
    m_helpButton = new QPushButton(name,this);
    connect(m_helpButton, SIGNAL(clicked()), this, SIGNAL(helpButtonPressed()));
    m_buttonLayout->addWidget(m_helpButton);

}

void TabDialogWrapper::showPage(QWidget *page)
{
    m_tabWidget->setCornerWidget(page);
}

void TabDialogWrapper::setCaption(QString cap)
{
    setWindowTitle(cap);
}

