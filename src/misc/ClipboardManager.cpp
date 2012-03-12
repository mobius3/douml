#include "misc/ClipboardManager.h"
#include <QClipboard>
#include <QApplication>
#include <QMimeSource>
#include <QMimeData>


ClipboardManager::ClipboardManager(QObject *_parent):QObject(_parent)
{}

QStringList ClipboardManager::GetStrings()
{
    return strings;
}
ClipboardManager::~ClipboardManager()
{}

void ClipboardManager::OnClipboardUpdate()
{
    QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* data = clipboard->mimeData();
    if(data->hasText())
        strings+=data->text();
}

void ClipboardManager::OnPutItemIntoClipboard(QString text)
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

