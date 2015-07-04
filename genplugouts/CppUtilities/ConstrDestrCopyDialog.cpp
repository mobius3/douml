
#ifdef WIN32
#include <stdlib.h>
#endif
#include "ConstrDestrCopyDialog.h"
#include "UmlClass.h"

#include <QList>

#include <gridbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlabel.h>
#include <hhbox.h>
#include <vvbox.h>
#include <qdir.h>
#include <QVBoxLayout>
#include "Logging/QsLog.h"
#include <QSettings>

class FunctionTracer
{
public:
//    FunctionTracer(QString val):traceString(val){qxtLog->debug(QString("   ").repeated(logLevel) + "Entered function " + traceString); logLevel++;}
//    ~FunctionTracer(){qxtLog->debug(QString("   ").repeated(logLevel) + "Left    function " + traceString);logLevel--;}
    FunctionTracer(QString val):traceString(val){QLOG_INFO() << "Entered function " + traceString;}
    ~FunctionTracer(){QLOG_INFO() <<  "Left    function " + traceString;}

    QString traceString;
    static int logLevel;
};

#define TRACE_FUNCTION FunctionTracer function_tracer(Q_FUNC_INFO);
//#define TRACE_FIELD_FUNCTION FunctionTracer function_tracer(Q_FUNC_INFO);
#define TRACE_FIELD_FUNCTION



ConstrDestrCopyDialog::ConstrDestrCopyDialog(UmlClass * cl, bool have_constructor,
        bool have_destructor, bool have_copy,
        bool have_const_copy, bool have_assignment,
        bool have_const_assignment)
    : QDialog(0), target(cl)
{
    setModal(true);
    QVBoxLayout * vbox = new QVBoxLayout(this);
    GridBox * g;
    QList<QLabel*> labels;
    QLabel * lbl;

    vbox->setSpacing(5);
    vbox->setMargin(5);

    lbl = new QLabel(QString("<big><b>C++ utilities for the class <i><tt>") +
                     (const char *) cl->name() + "</tt></i></b></big>",
                     this);
    lbl->setAlignment(Qt::AlignCenter);
    vbox->addWidget(lbl);

    // constructor

    g = new GridBox(2, this);
    vbox->addWidget(g);

    labels.append(lbl = new QLabel((have_constructor)
                             ? "the class already have contructor  "
                             : "the class doesn't have contructor  ",
                             g));
    g->addWidget(lbl);

    HHBox * h;
    g->addWidget(h = new HHBox(g));

    h->addWidget(add_constr = new QCheckBox("add constructor", h));
    h->addWidget(constr_explicit = new QCheckBox("explicit", h));

    // destructor

    if (! have_destructor) {
        g = new GridBox(2,this);
        vbox->addWidget(g);

        labels.append(lbl = new QLabel("the class doesn't have destructor  ",
                                 g));
        g->addWidget(lbl);

        h = new HHBox(g);
        g->addWidget(h);

        h->addWidget(add_destr = new QCheckBox("add destructor", h));
        h->addWidget(virtual_destr = new QCheckBox("virtual", h));
    }
    else
        add_destr = 0;

    // copy contructor

    if (have_copy) {
        add_copy = 0;

        if (!have_const_copy) {
            g = new GridBox(2, this);
            vbox->addWidget(g);

            labels.append(lbl = new QLabel("the class doesn't have copy contructor  \nwith const argument  ",
                                     g));
            g->addWidget(lbl);
            g->addWidget(add_const_copy = new QCheckBox("add copy constructor\nwith const argument",
                                           g));
        }
        else
            add_const_copy = 0;
    }
    else if (!have_const_copy) {
        g = new GridBox(2, this);
        vbox->addWidget(g);

        labels.append(lbl = new QLabel("the class doesn't have copy contructor  ",
                                 g));
        g->addWidget(lbl);

        VVBox * v = new VVBox(g);
        g->addWidget(v);
        v->addWidget(add_const_copy = new QCheckBox("add copy constructor\nwith const argument",
                                       v));
        v->addWidget(add_copy = new QCheckBox("add copy constructor\nwith non const argument",
                                 v));
    }
    else {
        g = new GridBox(2,this);
        vbox->addWidget(g);

        labels.append(lbl = new QLabel("the class doesn't have copy contructor  \nwith non const argument  ",
                                 g));
        g->addWidget(lbl);
        g->addWidget(add_copy = new QCheckBox("add copy constructor\nwith non const argument",
                                 g));
        add_const_copy = 0;
    }

    // assignment

    if (have_assignment) {
        add_assign = 0;

        if (!have_const_assignment) {
            g = new GridBox(2, this);
            vbox->addWidget(g);

            labels.append(lbl = new QLabel("the class doesn't have assignment\noperator with const argument  ",
                                     g));
            g->addWidget(lbl);
            g->addWidget(add_const_assign = new QCheckBox("add assignment\nwith const argument",
                                             g));
        }
        else
            add_const_assign = 0;
    }
    else if (!have_const_assignment) {
        g = new GridBox(2, this);
        vbox->addWidget(g);

        labels.append(lbl = new QLabel("the class doesn't have assignment operator  ", g));

        g->addWidget(lbl);
        VVBox * v = new VVBox(g);
        g->addWidget(v);

        v->addWidget(add_const_assign = new QCheckBox("add assignment\nwith const argument",
                                         v));
        v->addWidget(add_assign = new QCheckBox("add assignment\nwith non const argument",
                                   v));
    }
    else {
        g = new GridBox(2,this);
        vbox->addWidget(g);

        labels.append(lbl = new QLabel("the class doesn't have assignment operator  \nwith non const argument  ",
                                 g));
        g->addWidget(lbl);
        g->addWidget(add_assign = new QCheckBox("add assignment\nwith non const argument",
                                   g));
        add_const_assign = 0;
    }

    // use the same width for all the labels on the first column

    QSize sz(labels.first()->sizeHint());

    foreach (lbl,labels) {
        if (lbl->sizeHint().width() > sz.width())
            sz.setWidth(lbl->sizeHint().width());
    }

    foreach (lbl,labels) {
        sz.setHeight(lbl->sizeHint().height());
        lbl->setFixedSize(sz);
    }

    // ok & cancel buttons

    HHBox * hbox = new HHBox(this);

    vbox->addWidget(hbox);

    QPushButton * ok = new QPushButton("&OK", hbox);
    QPushButton * cancel = new QPushButton("&Cancel", hbox);
    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    QSize bs(cancel->sizeHint());

    ok->setDefault(TRUE);

    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void ConstrDestrCopyDialog::polish()
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

void ConstrDestrCopyDialog::accept()
{
    QLOG_INFO() << "Adding constructor";
    if (add_constr->isChecked())
        target->addContructor(constr_explicit->isChecked());
    QLOG_INFO() << "Adding destructor";
    if ((add_destr != 0) && add_destr->isChecked())
        target->addDestructor(virtual_destr->isChecked());
    QLOG_INFO() << "Adding copy constructor";
    if ((add_copy != 0) && add_copy->isChecked())
        target->addCopy(FALSE);
    QLOG_INFO() << "Adding const copy constructor";
    if ((add_const_copy != 0) && add_const_copy->isChecked())
        target->addCopy(TRUE);
    QLOG_INFO() << "Adding assign operator";
    if ((add_assign != 0) && add_assign->isChecked())
        target->addAssign(FALSE);
    QLOG_INFO() << "Adding const assign operator";
    if ((add_const_assign != 0) && add_const_assign->isChecked())
        target->addAssign(TRUE);

    QLOG_INFO() << "Accepting";
    QDialog::accept();
}

