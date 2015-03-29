#ifndef TOOLBARFACTORY_H
#define TOOLBARFACTORY_H
#include <QToolBar>
class QToolButton;
class ToolBarFactory
{
public:
    ToolBarFactory();
    static QToolButton *createToolButton(QPixmap icon, QWidget *receiver, const char *boundslot, QToolBar *parent, QString shown);
    static QToolButton *createToolButton(const QIcon & icon, const QString & textLabel, const QString & statusTip, QObject * receiver, const char * slot, QToolBar * parent, const char * name = 0);
};

#endif // TOOLBARFACTORY_H
