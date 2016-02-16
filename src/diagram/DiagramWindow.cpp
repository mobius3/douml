// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************




#include <QMdiArea>
#include <qnamespace.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <QToolBar>
#include <qtoolbutton.h>
#include <qwhatsthis.h>
#include <qlabel.h>
#include <qcursor.h>
//Added by qt3to4:
#include <QTextStream>
#include <QTextStream>




#include "BrowserDiagram.h"
#include "DiagramWindow.h"
#include "DiagramView.h"
#include "UmlCanvas.h"
#include "UmlWindow.h"
#include "myio.h"
#include "UmlPixmap.h"
#include "translate.h"
#include <QLayout>
#include "toolbarfactory.h"

static QString zoomText()
{
    return QObject::tr("Enter a new scale value or use the arrows to change the <i>scale</i>");
}
static QString fitzoomText()
{
    return QObject::tr("Click this button to compute the <i>fit scale</i> allowing to try to show all the diagram");
}
static QString optwinsizeText()
{
    return QObject::tr("Click this button to compute the smallest window size allowing to show all the diagram");
}
static QString editText()
{
    return QObject::tr("Click this button to call the diagram menu like on a right mouse click"
              " done out of any element");
}

DiagramWindow::DiagramWindow(BrowserDiagram * br, const QString & s)
    : QMainWindow(0 /*,(const char *) s, Qt::WA_DeleteOnClose*/),
      no_save(FALSE), browser_node(br)
{
    setWindowTitle(s);
    setAttribute(Qt::WA_DeleteOnClose);
    canvas = new UmlCanvas(br->get_format(), br);
    setFocusPolicy(Qt::StrongFocus);
    /* [lgfreitas] Fixing bug 3153814 and 3153824 where MDI config was lost and artifact outline were lost */
    m_containingSubWindow = UmlWindow::get_workspace()->addSubWindow(this); // workspace now needs to have windows added
    if(UmlWindow::get_workspace()->currentSubWindow() && !UmlWindow::get_workspace()->currentSubWindow()->isMaximized())
        UmlWindow::get_workspace()->cascadeSubWindows();
    //sw->resize(300, 300);
}

DiagramWindow::~DiagramWindow()
{
    browser_node->set_window_destroyed();
    m_containingSubWindow->deleteLater();
    delete canvas;
}

void DiagramWindow::call_menu()
{
    edit->setDown(FALSE);
    get_view()->menu(QCursor::pos());
}

void DiagramWindow::raise()
{
    showNormal();
    setFocus();
}

void DiagramWindow::selectOn()
{
    select->setEnabled(TRUE);
    hit_select();
}

void DiagramWindow::hit_select()
{
    hit_button(UmlSelect, select);
}

void DiagramWindow::add_edit_button(QToolBar * toolbar)
{
    //edit = new QToolButton(*editButton, QObject::tr("edit"), QString(),
      //                     this, SLOT(call_menu()), toolbar, "edit");
    edit = new QToolButton(toolbar);
    edit->setIcon(QIcon(*editButton));
    edit->setText(tr("edit"));
    edit->setObjectName("edit");
    connect(edit, SIGNAL(clicked()), this, SLOT(call_menu()));
    edit->setWhatsThis(editText());

    edit->setCheckable(FALSE);
    toolbar->addWidget(edit);
}

void DiagramWindow::add_scale_cmd(QToolBar *toolbar)
{
    sb_zoom = new QSpinBox( /*SCALE_MAX, 10, */toolbar/*, QObject::tr("scale")*/);
    sb_zoom->setMinimum(SCALE_MIN);
    sb_zoom->setMaximum(SCALE_MAX);
    sb_zoom->setSingleStep(10);
    sb_zoom->setObjectName(tr("scale"));
    //sb_zoom->setPrefix("scale ");
    sb_zoom->setSuffix("%");
    sb_zoom->setValue(100);
    connect(sb_zoom, SIGNAL(valueChanged(int)), this, SLOT(new_scale(int)));
    sb_zoom->setWhatsThis(zoomText());
    toolbar->addWidget(sb_zoom);
    //Q3WhatsThis::add(sb_zoom, zoomText());

    QToolButton * fitscale =
        ToolBarFactory::createToolButton(*fitscaleButton, QObject::tr("optimal scale"), QString(),
                        this, SLOT(fit_scale()), toolbar, "optimal scale");

    fitscale->setWhatsThis(fitzoomText());
    //Q3WhatsThis::add(fitscale, fitzoomText());

    //

    optwinsize = ToolBarFactory::createToolButton(*optwindowsizeButton, QObject::tr("optimal window size"), QString(),
                                 this, SLOT(optimal_window_size()), toolbar, "optimal window size");


    optwinsize->setWhatsThis(fitzoomText());
    //Q3WhatsThis::add(optwinsize, optwinsizeText());

    optwinsize->setCheckable(FALSE);
}

void DiagramWindow::new_scale(int percent)
{
    double np = ((double) percent) / 100.0;

    if (canvas->zoom() != np) {
        get_view()->set_zoom(np);
        sb_zoom->setValue(percent);
    }
}

void DiagramWindow::fit_scale()
{
    get_view()->fit_scale();
    sb_zoom->setValue((int)(canvas->zoom() * 100));
}

void DiagramWindow::optimal_window_size()
{
    get_view()->do_optimal_window_size();
}

void DiagramWindow::change_zoom(int n)
{
    int z = sb_zoom->value() + n;

    new_scale((z > 200)
              ? 200
              : ((z < 30) ? 30 : z));
}

void DiagramWindow::package_modified() const
{
    browser_node->package_modified();
}

bool DiagramWindow::frozen() const
{
    return (BrowserNode::edition_active() ||
            !browser_node->is_writable());
}

void DiagramWindow::save_session(QTextStream & st)
{
    // can't access to the window position, even through geometry
    QString warning;
    st << "  ";
    ((BrowserNode *) browser_node)->save(st, TRUE, warning);
    st << "\n    " << width() << " " << height() << " ";
    get_view()->save_session(st);

}

void DiagramWindow::read_session(char *& st)
{






    unsigned w = read_unsigned(st);

    resize(w, read_unsigned(st));

    new_scale(read_unsigned(st));
    get_view()->read_session(st);
}

void DiagramWindow::session_window_size()
{



}

void DiagramWindow::save(const char * ext, QString & warning,
                         BooL & is_new) const
{
    double zm  = canvas->zoom();

    if (zm != 1)
        get_view()->set_zoom(1);

    QString diagram_def;
    QTextStream st(&diagram_def, QIODevice::WriteOnly);
    st.setCodec("UTF-8");
    int current_indent = indent();

    indent0();
    get_view()->save(st, warning, FALSE);
    st.flush();
    save_definition(browser_node->get_ident(), ext, diagram_def, is_new);
    indent(current_indent);

    if (zm != 1)
        get_view()->set_zoom(zm);

}

void DiagramWindow::duplicate(int dest_id, const char * ext) const
{
    QString warning;
    double zm  = canvas->zoom();

    if (zm != 1)
        get_view()->set_zoom(1);

    QString diagram_def;
    QTextStream st(&diagram_def, QIODevice::WriteOnly); //[lgfreitas] it was nothing but some inlines to do this
    st.setCodec("UTF-8");
    int current_indent = indent();
    BooL is_new = TRUE;

    indent0();
    get_view()->save(st, warning, FALSE);
    st.flush();
    save_definition(dest_id, ext, diagram_def.toLatin1().constData(), is_new);
    indent(current_indent);

    if (zm != 1)
        get_view()->set_zoom(zm);

}

QString DiagramWindow::copy_selected() const
{
    QString diagram_def;
    QString warning;
    double zm  = canvas->zoom();

    if (zm != 1)
        get_view()->set_zoom(1);


    QTextStream st(&diagram_def, QIODevice::WriteOnly);
    st.setCodec("UTF-8");

    indent0();
    get_view()->save(st, warning, TRUE);
    st.flush();

    if (zm != 1)
        get_view()->set_zoom(zm);
    return diagram_def;
}

