
#ifdef WIN32
#include <stdlib.h>
#endif

#include "Dialog.h"
#include "UmlArtifact.h"
#include "SmallPushButton.h"

#include <qlineedit.h>
#include <QTextEdit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qlabel.h>
#include <gridbox.h>
#include "hhbox.h"
#include <qdir.h>
#include <QByteArray>
#include <QVBoxLayout>
#include <QSettings>

Dialog::Dialog(UmlArtifact * art, const QByteArray & path_exe, QByteArray & pro, QByteArray & target, QByteArray & tmplt, QByteArray & config, QByteArray & defines, QByteArray & includepath, QByteArray & dependpath, QByteArray & objectsdir, QByteArray & footer)
    : QDialog(0), _art(art), _pro(pro), _target(target), _tmplt(tmplt),
      _config(config), _defines(defines), _includepath(includepath), _dependpath(dependpath),
      _objectsdir(objectsdir), _footer(footer)
{
    setModal(true);
    QDir d(path_exe);
    QVBoxLayout * vbox = new QVBoxLayout(this);
    GridBox * grid = new GridBox(2, this);
    HHBox * htab;
    int index;

    vbox->addWidget(grid);
    vbox->setMargin(5);

    grid->addWidget(new QLabel(".pro file : ", grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edpro = new QLineEdit(htab));
    edpro->setText(d.absoluteFilePath(pro));

    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(browsepro = new SmallPushButton("browse", htab));
    connect(browsepro, SIGNAL(clicked()), this, SLOT(browse_pro()));

    grid->addWidget(new QLabel("target : ", grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edtarget = new QLineEdit(htab));
    edtarget->setText(d.absoluteFilePath(target));
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(browsetarget = new SmallPushButton("browse", htab));
    connect(browsetarget, SIGNAL(clicked()), this, SLOT(browse_target()));

    grid->addWidget(new QLabel("template : ", grid));
    grid->addWidget(cbtemplate = new QComboBox(grid));
    cbtemplate->setEditable(true);

    static const char * templates[] = { "app", "lib", "subdirs" };
    bool find = FALSE;

    for (index = 0; index != sizeof(templates) / sizeof(*templates); index += 1) {
        cbtemplate->addItem(templates[index]);

        if (tmplt == templates[index]) {
            cbtemplate->setCurrentIndex(index);
            find = TRUE;
        }
    }

    if (! find) {
        cbtemplate->addItem((QString) tmplt);
        cbtemplate->setCurrentIndex(index);
    }

    grid->addWidget(new QLabel("config : ", grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(cbconf[0] = new QComboBox( htab));
    cbconf[0]->addItem("debug");
    cbconf[0]->addItem("release");

    QStringList lcnf = QString(config).split(" ");
        //QStringList::split(" ", (const char *) config);
    QStringList::Iterator it = lcnf.begin();

    cbconf[0]->setCurrentIndex((*it++ == "debug") ? 0 : 1);

    htab->addWidget(cbconf[1] = new QComboBox( htab));
    cbconf[1]->addItem("warn_on");
    cbconf[1]->addItem("warn_off");
    cbconf[1]->setCurrentIndex((*it++ == "warn_on") ? 0 : 1);

    QSizePolicy sp = cbconf[0]->sizePolicy();

    sp.setHorizontalPolicy(QSizePolicy::Fixed);
    cbconf[0]->setSizePolicy(sp);
    cbconf[1]->setSizePolicy(sp);

    htab->addWidget(new QLabel(" qt ", htab));
    it++;	// qt

    /*const char * configs[] = {
        "", "opengl", "thread", "x11", "windows",
        "console", "dll", "staticlib", 0
    };*/
    QStringList configs;
    configs<<""<<"opengl"<<"thread"<<"x11"<<"windows"<<
            "console"<<"dll"<<"staticlib";

    for (index = 2;
         index != sizeof(cbconf) / sizeof(*cbconf) - 1;
         index += 1) {
        htab->addWidget(cbconf[index] = new QComboBox( htab));
        cbconf[index]->setEditable(true);

        if (it != lcnf.end())
            cbconf[index]->addItem(*it++);

        cbconf[index]->addItems(configs);
        cbconf[index]->setCurrentIndex(0);
    }

    htab->addWidget(cbconf[index] = new QComboBox( htab));
    cbconf[index]->setEditable(true);

    if (it != lcnf.end()) {
        QString s = *it++;

        while (it != lcnf.end())
            s += " " + *it++;

        cbconf[index]->addItem(s);
    }

    cbconf[index]->addItems(configs);
    cbconf[index]->setCurrentIndex(0);


    grid->addWidget(new QLabel("defines : ", grid));
    grid->addWidget(eddefines = new QLineEdit(grid));
    eddefines->setText(defines);

    ///may be computed
    grid->addWidget(new QLabel("include paths : ", grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edincludepath = new QLineEdit(htab));
    edincludepath->setText(includepath);
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(computeincludepath = new SmallPushButton("compute", htab));
    connect(computeincludepath, SIGNAL(clicked()), this, SLOT(compute_includepath()));

    grid->addWidget(new QLabel("depend paths : ", grid));
    grid->addWidget(eddependpath = new QLineEdit(grid));
    eddependpath->setText(dependpath);

    grid->addWidget(new QLabel("objects dir : ", grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(edobjectsdir = new QLineEdit(htab));
    edobjectsdir->setText(objectsdir);
    htab->addWidget(new QLabel(" ", htab));
    htab->addWidget(browseobjectsdir = new SmallPushButton("browse", htab));
    connect(browseobjectsdir, SIGNAL(clicked()), this, SLOT(browse_objectsdir()));

    grid->addWidget(new QLabel("footer : ", grid));
    grid->addWidget(edfooter = new QTextEdit(grid));
    edfooter->setText(footer);

    grid->addWidget(new QLabel(grid));
    grid->addWidget(new QLabel(grid));

    grid->addWidget(new QLabel(grid));
    grid->addWidget(htab = new HHBox(grid));
    htab->addWidget(new QLabel(htab));
    QPushButton * ok ;
    htab->addWidget(ok = new QPushButton("&OK", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * cancel;
    htab->addWidget( cancel = new QPushButton("&Cancel", htab));
    htab->addWidget(new QLabel(htab));
    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);

    if (ok->sizeHint().width() > bs.width())
        bs.setWidth(ok->sizeHint().width());

    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void Dialog::polish()
{
    QDialog::ensurePolished();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "DoUML", "settings");
    settings.setIniCodec("UTF-8");
    int l, t, r, b;
    l = settings.value("Desktop/left", -1).toInt();
    r = settings.value("Desktop/right", -1).toInt();
    t = settings.value("Desktop/top", -1).toInt();
    b = settings.value("Desktop/bottom", -1).toInt();

    if(l != -1 && r != -1 && t != -1 && b != -1)
    {
      if (!((r == 0) && (t == 0) && (r == 0) && (b == 0)) &&
          !((r < 0) || (t < 0) || (r < 0) || (b < 0)) &&
          !((r <= l) || (b <= t)))
      {
        int cx = (r + l) / 2;
        int cy = (t + b) / 2;

        move(x() + cx - (x() + width() / 2), y() + cy - (y() + height() / 2));
      }
    }
}

void Dialog::accept()
{
    _pro = edpro->text().toLatin1();
    _target = edtarget->text().toLatin1();
    _objectsdir = edobjectsdir->text().toLatin1();
    _tmplt = cbtemplate->currentText().toLatin1();

    int index;

    _config = QString(cbconf[0]->currentText() + " " + cbconf[1]->currentText() + " qt").toLatin1();

    for (index = 2; index != sizeof(cbconf) / sizeof(*cbconf); index += 1) {
        QString s = cbconf[index]->currentText();

        if (! s.isEmpty())
            _config += " " + s;
    }

    _defines = eddefines->text().toLatin1();
    _includepath = edincludepath->text().toLatin1();
    _dependpath = eddependpath->text().toLatin1();
    _objectsdir = edobjectsdir->text().toLatin1();
    _footer = edfooter->toPlainText().toLatin1();

    QDialog::accept();
}

void Dialog::browse_pro()
{
    QString f = QFileDialog::getSaveFileName(this, "specify .pro file",edpro->text(), "Pro file (*.pro)");

    if (! f.isEmpty())
        edpro->setText(f);
}

void Dialog::browse_target()
{
    QString f = QFileDialog::getSaveFileName(this, "specify target file",edtarget->text(), "");

    if (! f.isEmpty())
        edtarget->setText(f);
}

void Dialog::compute_includepath()
{
    const QVector<UmlArtifact*> & arts = _art->associatedArtifacts();
    QFileInfo fi(edpro->text());
    QString prodir = fi.path();
    unsigned index;
    QStringList l;

    for (index = 0; index != arts.count(); index += 1) {
        QString s = arts[index]->way(prodir, TRUE);

        if ((s != "./") && (l.indexOf(s) == -1))
            l.append(s);
    }

    edincludepath->setText(l.join(" "));

}

void Dialog::browse_objectsdir()
{
    QString d = QFileDialog::getExistingDirectory(this, "select objects dir", edobjectsdir->text() );

    if (! d.isEmpty()) {
#ifdef WIN32
        QDir dir(d);

        if (! dir.exists()) {
            int index = d.length() - 1;

            if (d.at(index) == QChar('/'))
                index -= 1;

            QString d2 = d;

            d2.remove(index, 1);

            QDir dir2(d2);

            if (dir2.exists())
                d = d2;
        }

#endif

        edobjectsdir->setText(d);
    }
}

