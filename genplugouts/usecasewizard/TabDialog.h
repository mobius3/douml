#ifndef _TABDIALOG_H
#define _TABDIALOG_H


#include <q3tabdialog.h>
#include <qstring.h>
#include <q3cstring.h>

class Q3TextEdit;
class UmlUseCase;

//Only for C++
//don't colapse the C++ & Java definition in only one class because this is too artificial
//note : the stereotype doesn't have special meaning for Bouml, I use it just to inform
class TabDialog : public Q3TabDialog
{
    Q_OBJECT

public:
    TabDialog(UmlUseCase * u);


protected:
    UmlUseCase * uc;

    QTextCodec * Codec;


public:
    Q3TextEdit * summary;

    Q3TextEdit * context;

    Q3TextEdit * precond;

    Q3TextEdit * description;

    Q3TextEdit * postcond;

    Q3TextEdit * exceptions;


protected:
    QPoint desktopCenter;

protected slots:
    virtual void polish();


public:
    void accept();

    void reject();


private:
    QString toUnicode(const char * str);

    void latinize(QString & s);

    Q3CString fromUnicode(const QString & s);

};

#endif
