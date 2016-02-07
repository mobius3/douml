#ifndef _TABDIALOG_H
#define _TABDIALOG_H


#include "tabdialogwrapper.h"
#include <qstring.h>


class QTextEdit;
class UmlUseCase;

//Only for C++
//don't colapse the C++ & Java definition in only one class because this is too artificial
//note : the stereotype doesn't have special meaning for Bouml, I use it just to inform
class TabDialog : public TabDialogWrapper
{
    Q_OBJECT

public:
    TabDialog(UmlUseCase * u);

protected:
    UmlUseCase * uc;
    QTextCodec * Codec;

public:
    QTextEdit * summary;
    QTextEdit * context;
    QTextEdit * precond;
    QTextEdit * description;
    QTextEdit * postcond;
    QTextEdit * exceptions;

protected:
    QPoint desktopCenter;

protected slots:
    virtual void polish();

public:
    virtual void accept() override;
    virtual void reject() override;

private:
    QString toUnicode(const char * str);
    void latinize(QString & s);
    QByteArray fromUnicode(const QString & s);
};

#endif
