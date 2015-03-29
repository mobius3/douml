
#include "Dialog.h"

#ifdef WIN32
#include <stdlib.h>
#endif

#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <HHBox.h>
#include <qcheckbox.h>
#include <qdir.h>
//Added by qt3to4:
#include <QVBoxLayout>
#include <QSettings>

Dialog::Dialog(BooL & rec, char & lang) : QDialog(0), _rec(rec), _lang(lang)
{
    setModal(true);
    QVBoxLayout * vbox = new QVBoxLayout(this);
    HHBox * htab;

    vbox->setMargin(5);

    // recursive checkbox
    if (rec) {
        htab = new HHBox(this);
        htab->setMargin(5);
        vbox->addWidget(htab);

        htab->addWidget(rec_cb = new QCheckBox("Do recursively", htab));
    }
    else
        rec_cb = 0;

    // langs + cancel buttons

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    QPushButton * cpp;
    htab->addWidget(cpp = new QPushButton("&C++", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * java;
    htab->addWidget(java = new QPushButton("&Java", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * idl;
    htab->addWidget(idl = new QPushButton("&Idl", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * php;
    htab->addWidget(php = new QPushButton("P&hp", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * python;
    htab->addWidget(python = new QPushButton("P&ython", htab));
    htab->addWidget(new QLabel(htab));
    QPushButton * cancel;
    htab->addWidget(cancel = new QPushButton("&Cancel", htab));
    htab->addWidget(new QLabel(htab));
    QSize bs(cancel->sizeHint());

    cpp->setFixedSize(bs);
    java->setFixedSize(bs);

    connect(cpp, SIGNAL(clicked()), this, SLOT(accept_cpp()));
    connect(java, SIGNAL(clicked()), this, SLOT(accept_java()));
    connect(idl, SIGNAL(clicked()), this, SLOT(accept_idl()));
    connect(php, SIGNAL(clicked()), this, SLOT(accept_php()));
    connect(python, SIGNAL(clicked()), this, SLOT(accept_python()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    // help

    htab = new HHBox(this);
    htab->setMargin(5);
    vbox->addWidget(htab);

    htab->addWidget(new QLabel(htab));
    htab->addWidget(new QLabel("Warning : reset the declarations/definitions to\n"
               "their default value from the 'generation settings'", htab));
    htab->addWidget(new QLabel(htab));
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

void Dialog::accept_cpp()
{
    _lang = 'c';

    accept();
}

void Dialog::accept_java()
{
    _lang = 'j';
    accept();
}

void Dialog::accept_idl()
{
    _lang = 'i';
    accept();
}

void Dialog::accept_php()
{
    _lang = 'h';
    accept();
}

void Dialog::accept_python()
{
    _lang = 'y';
    accept();
}

void Dialog::accept()
{
    _rec = (rec_cb) ? rec_cb->isChecked() : FALSE;

    QDialog::accept();
}

