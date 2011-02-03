#ifndef _TABDIALOG_H
#define _TABDIALOG_H


#include <q3tabdialog.h>
#include <qstring.h>
#include <q3cstring.h>

class Q3MultiLineEdit;
class UmlUseCase;

//Only for C++
//don't colapse the C++ & Java definition in only one class because this is too artificial
//note : the stereotype doesn't have special meaning for Bouml, I use it just to inform
class TabDialog : public Q3TabDialog {
  Q_OBJECT

  public:
    TabDialog(UmlUseCase * u);


  protected:
    UmlUseCase * uc;

    QTextCodec * Codec;


  public:
    Q3MultiLineEdit * summary;

    Q3MultiLineEdit * context;

    Q3MultiLineEdit * precond;

    Q3MultiLineEdit * description;

    Q3MultiLineEdit * postcond;

    Q3MultiLineEdit * exceptions;


  protected:
    QPoint desktopCenter;

protected slots:    virtual void polish();


  public:
    void accept();

    void reject();


  private:
    QString toUnicode(const char * str);

    void latinize(QString & s);

    Q3CString fromUnicode(const QString & s);

};

#endif
