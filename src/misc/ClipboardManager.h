#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QStringList>
#include "misc/SingletonHolder.h"

class ClipboardManager : public QObject
{
Q_OBJECT
public:
    ClipboardManager(QObject* _parent = 0);
    ~ClipboardManager();
    QStringList GetStrings();
public slots:
    virtual void OnClipboardUpdate();
    //void OnClipboardDataRequested();
    virtual void OnPutItemIntoClipboard(QString);
private:
    QStringList strings;
};
BIND_TO_SELF_SINGLE(ClipboardManager);
#endif // CLIPBOARDMANAGER_H
