#ifndef _DIALOG_H
#define _DIALOG_H


#include <q3cstring.h>

#include "qdialog.h"

class UmlArtifact;
class SmallPushButton;

class QLineEdit;
class Q3TextEdit;
class QPushButton;
class Q3ComboBox;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(UmlArtifact * art, const Q3CString & path_exe, Q3CString & pro, Q3CString & target, Q3CString & tmplt, Q3CString & config, Q3CString & defines, Q3CString & includepath, Q3CString & dependpath, Q3CString & objectsdir, Q3CString & footer);

protected:
    UmlArtifact * _art;

    Q3CString & _pro;

    Q3CString & _target;

    Q3CString & _tmplt;

    Q3CString & _config;

    Q3CString & _defines;

    Q3CString & _includepath;

    Q3CString & _dependpath;

    Q3CString & _objectsdir;

    Q3CString & _footer;

    QLineEdit * edpro;

    QPushButton * browsepro;

    QLineEdit * edtarget;

    QPushButton * browsetarget;

    Q3ComboBox * cbtemplate;

    Q3ComboBox * cbconf[5];

    QLineEdit * eddefines;

    QLineEdit * edincludepath;

    SmallPushButton * computeincludepath;

    QLineEdit * eddependpath;

    QLineEdit * edobjectsdir;

    QPushButton * browseobjectsdir;

    Q3TextEdit * edfooter;

protected slots:
    virtual void polish();

    virtual void accept();
    void browse_pro();
    void browse_target();
    void compute_includepath();
    void browse_objectsdir();
};

#endif
