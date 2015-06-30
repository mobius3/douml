#ifndef _DIALOG_H
#define _DIALOG_H


#include <QByteArray>

#include "qdialog.h"

class UmlArtifact;
class SmallPushButton;

class QLineEdit;
class QTextEdit;
class QPushButton;
class QComboBox;

class Dialog : public QDialog
{
    Q_OBJECT
  public:
    Dialog(UmlArtifact * art, const QByteArray & path_exe, QByteArray & pro, QByteArray & target, QByteArray & tmplt, QByteArray & config, QByteArray & defines, QByteArray & includepath, QByteArray & dependpath, QByteArray & objectsdir, QByteArray & footer);

  protected:
    UmlArtifact * _art;

    QByteArray & _pro;

    QByteArray & _target;

    QByteArray & _tmplt;

    QByteArray & _config;

    QByteArray & _defines;

    QByteArray & _includepath;

    QByteArray & _dependpath;

    QByteArray & _objectsdir;

    QByteArray & _footer;

    QLineEdit * edpro;

    QPushButton * browsepro;

    QLineEdit * edtarget;

    QPushButton * browsetarget;

    QComboBox * cbtemplate;

    QComboBox * cbconf[5];

    QLineEdit * eddefines;

    QLineEdit * edincludepath;

    SmallPushButton * computeincludepath;

    QLineEdit * eddependpath;

    QLineEdit * edobjectsdir;

    QPushButton * browseobjectsdir;

    QTextEdit * edfooter;

protected slots:
    virtual void polish();

    virtual void accept();
    void browse_pro();
    void browse_target();
    void compute_includepath();
    void browse_objectsdir();
};

#endif
