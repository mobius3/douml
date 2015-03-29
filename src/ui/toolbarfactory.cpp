#include "toolbarfactory.h"
#include <QToolButton>
#include <QLayout>
ToolBarFactory::ToolBarFactory()
{
}
QToolButton *
ToolBarFactory::createToolButton(
        QPixmap icon,
        QWidget * receiver,
        const char * boundslot,
        QToolBar * parent,
        QString shown)
{
    QToolButton * newButton = new QToolButton(parent);
    QObject::connect(newButton, SIGNAL(clicked()), receiver, boundslot);
    newButton->setIcon(icon);
    newButton->setText(shown);
    newButton->setToolTip(shown);
    newButton->setMinimumSize(30, 30);
    parent->addWidget(newButton);
    return newButton;
}


QToolButton *ToolBarFactory::createToolButton(const QIcon &icon, const QString &textLabel, const QString &statusTip, QObject *receiver,
                                              const char *slot, QToolBar *parent, const char *name)
{
    QToolButton *newButton = new QToolButton(parent);
    QObject::connect(newButton, SIGNAL(clicked()), receiver, slot);
    newButton->setIcon(icon);
    newButton->setText(textLabel);
    newButton->setToolTip(statusTip);
    newButton->setMinimumSize(30, 30);
    parent->addWidget(newButton);
    newButton->setToolTip(name);
    return newButton;
}
