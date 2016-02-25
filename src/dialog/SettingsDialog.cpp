// *************************************************************************
//
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





#include <hhbox.h>
#include <gridbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>

#include "Settings.h"
#include "SettingsDialog.h"
#include "UmlPixmap.h"
#include "UmlDesktop.h"
#include "translate.h"
#include "widgetwithlayout.h"
#include <QLayout>
void ColorSpecVector::resize(int s)
{
    ColorSpec * v = new ColorSpec[s];

    for (int i = 0; i != _size; i += 1)
        v[i] = _v[i];

    delete [] _v;
    _v = v;
    _size = s;
}

class ComboStates : public QComboBox
{
public:
    ComboStates(QWidget * parent, Uml3States v, bool nodefault, bool unchanged);
    ComboStates(QWidget * parent, ClassDrawingMode v, bool nodefault, bool unchanged);
    ComboStates(QWidget * parent, DrawingLanguage v, bool nodefault, bool unchanged);
    ComboStates(QWidget * parent, ShowContextMode v, bool nodefault, bool unchanged);
    ComboStates(QWidget * parent, char v, bool nodefault, bool unchanged);

    virtual QSize sizeHint() const override;
};

ComboStates::ComboStates(QWidget * parent, Uml3States v,
                         bool nodefault, bool unchanged)
    : QComboBox(parent)
{
    this->setEditable(false);
    addItem(tr(stringify((Uml3States) 0)));
    addItem(tr(stringify((Uml3States) 1)));

    // the last value MUST be default
    if (!nodefault)
        addItem(tr(stringify((Uml3States) 2)));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else
        setCurrentIndex(v);
}

ComboStates::ComboStates(QWidget * parent, ClassDrawingMode v,
                         bool nodefault, bool unchanged)
    : QComboBox( parent)
{
    int i;
    this->setEditable(false);
    for (i = 0; i != (int) DefaultClassDrawingMode; i += 1)
        addItem(tr(stringify((ClassDrawingMode) i)));

    // the last value MUST be default
    if (!nodefault)
        addItem(tr(stringify((ClassDrawingMode) i)));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else
        setCurrentIndex(v);
}

ComboStates::ComboStates(QWidget * parent, DrawingLanguage v,
                         bool nodefault, bool unchanged)
    : QComboBox(parent)
{
    int i;
    this->setEditable(false);
    for (i = 0; i != (int) DefaultDrawingLanguage; i += 1)
        addItem(stringify((DrawingLanguage) i));

    // the last value MUST be default
    if (!nodefault)
        addItem(tr(stringify((DrawingLanguage) i)));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else
        setCurrentIndex(v);
}

static QString _2space(QString s)
{
    int index = s.indexOf("_");

    return (index == -1) ? s : s.replace(index, 1, " ");
}

ComboStates::ComboStates(QWidget * parent, ShowContextMode v,
                         bool nodefault, bool unchanged)
    : QComboBox(parent)
{
    int i;
    this->setEditable(false);
    for (i = 0; i != (int) DefaultShowContextMode; i += 1)
        addItem(_2space(tr(stringify((ShowContextMode) i))));

    // the last value MUST be default
    if (!nodefault)
        addItem(_2space(tr(stringify((ShowContextMode) i))));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else
        setCurrentIndex(v);
}


ComboStates::ComboStates(QWidget * parent, char v,
                         bool nodefault, bool unchanged)
    : QComboBox(parent)
{
    int i;
    this->setEditable(false);
    for (i = MinMemberWidthValue; i != SupMemberWidthValue; i += 1) {
        char s[4];

        sprintf(s, "%d", i);
        addItem(s);
    }

    addItem(tr("unlimited"));

    if (!nodefault)
        addItem(tr("default"));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else {
        switch (v) {
        case UmlDefaultMaxMemberWidth:
            setCurrentIndex(SupMemberWidthValue - MinMemberWidthValue + 1);
            break;

        case UmlUnlimitedMemberWidth:
            setCurrentIndex(SupMemberWidthValue - MinMemberWidthValue);
            break;

        default:
            setCurrentIndex(v - MinMemberWidthValue);
            break;
        }
    }
}

QSize ComboStates::sizeHint() const
{
    QSize sz = QComboBox::sizeHint();

    sz.setHeight(fontMetrics().height() + 1);
    return sz;
}


class ComboColor : public QComboBox
{
public:
    ComboColor(QWidget * parent, UmlColor v,
               bool nodefault, bool unchanged);
};

ComboColor::ComboColor(QWidget * parent, UmlColor v,
                       bool nodefault, bool unchanged)
    : QComboBox(parent)
{
    QString s_transparent = QObject::tr("Transparent");
    QString s_unknown_color = QObject::tr("Unknown color");
    this->setEditable(false);
    // the last value MUST be default
    for (int i = 0; i != (int) UmlDefaultColor; i += 1) {
        // use switch to not be dependant on the colors items order and number
        switch (i) {
        case UmlTransparent:
            addItem(s_transparent);
            break;

        case UmlWhite:
            addItem(QIcon(* WhitePixmap), "");
            break;

        case UmlLightYellow:
            addItem(QIcon(* LightYellowPixmap), "");
            break;

        case UmlYellow:
            addItem(QIcon(* YellowPixmap), "");
            break;

        case UmlMediumYellow:
            addItem(QIcon(* MediumYellowPixmap), "");
            break;

        case UmlDarkYellow:
            addItem(QIcon(* DarkYellowPixmap), "");
            break;

        case UmlLightBlue:
            addItem(QIcon(* LightBluePixmap), "");
            break;

        case UmlBlue:
            addItem(QIcon(* BluePixmap), "");
            break;

        case UmlLightMediumBlue:
            addItem(QIcon(* LightMediumBluePixmap), "");
            break;

        case UmlMediumBlue:
            addItem(QIcon(* MediumBluePixmap), "");
            break;

        case UmlDarkBlue:
            addItem(QIcon(* DarkBluePixmap), "");
            break;

        case UmlLightGreen:
            addItem(QIcon(* LightGreenPixmap), "");
            break;

        case UmlGreen:
            addItem(QIcon(* GreenPixmap), "");
            break;

        case UmlLightMediumGreen:
            addItem(QIcon(* LightMediumGreenPixmap), "");
            break;

        case UmlMediumGreen:
            addItem(QIcon(* MediumGreenPixmap), "");
            break;

        case UmlDarkGreen:
            addItem(QIcon(* DarkGreenPixmap), "");
            break;

        case UmlLightRed:
            addItem(QIcon(* LightRedPixmap), "");
            break;

        case UmlMidRed:
            addItem(QIcon(* MidRedPixmap), "");
            break;

        case UmlRed:
            addItem(QIcon(* RedPixmap), "");
            break;

        case UmlVeryLightOrange:
            addItem(QIcon(* VeryLightOrangePixmap), "");
            break;

        case UmlLightOrange:
            addItem(QIcon(* LightOrangePixmap), "");
            break;

        case UmlOrange:
            addItem(QIcon(* OrangePixmap), "");
            break;

        case UmlDarkOrange:
            addItem(QIcon(* DarkOrangePixmap), "");
            break;

        case UmlLightMagenta:
            addItem(QIcon(* LightMagentaPixmap), "");
            break;

        case UmlMagenta:
            addItem(QIcon(* MagentaPixmap), "");
            break;

        case UmlMidMagenta:
            addItem(QIcon(* MidMagentaPixmap), "");
            break;

        case UmlDarkMagenta:
            addItem(QIcon(* DarkMagentaPixmap), "");
            break;

        case UmlVeryLightGray:
            addItem(QIcon(* VeryLightGrayPixmap), "");
            break;

        case UmlLightGray:
            addItem(QIcon(* LightGrayPixmap), "");
            break;

        case UmlGray:
            addItem(QIcon(* GrayPixmap), "");
            break;

        case UmlDarkGray:
            addItem(QIcon(* DarkGrayPixmap), "");
            break;

        case UmlBlack:
            addItem(QIcon(* BlackPixmap), "");
            break;

        default:
            addItem(s_unknown_color);
        }
    }

    if (!nodefault)
        addItem(tr(stringify(UmlDefaultColor)));

    if (unchanged) {
        addItem(tr("<unchanged>"));
        setCurrentIndex(count() - 1);
    }
    else
        setCurrentIndex(v);




    //setSizeLimit(25);	// yes !, don't set it to count() ! //[lgfreitas] Qt4 complains it does not exists.

}

QSize SettingsDialog::previous_size;
QPoint SettingsDialog::previous_position;
QString SettingsDialog::previous_active_tab;

SettingsDialog::SettingsDialog(StateSpecVector * st, ColorSpecVector * co,
                               bool nodefault, bool unchanged, QString title)
    : TabDialog(0, title, TRUE),
      states(st), colors(co), first_visible_page(0),
      several(unchanged), did_apply(FALSE)
{
    setWindowTitle((title.isEmpty()) ? QObject::tr("Diagram Drawing Settings dialog") : title);

    QString s_diagram = QObject::tr("diagram");

    QWidget * grid = 0;

    QString tabname;
    unsigned i;
    unsigned n;

    if (states != 0) {
        n = states->size();
        cbstates = new QHash<int,ComboStates*>;

        for (i = 0; i != n; i += 1) {
            StateSpec & st = states->at(i);
            QString s = st.name;
            int index = s.indexOf('#');
            QString tbn;

            if (index != -1) {
                tbn = s.left(index);
                s = s.mid(index + 1);
            }
            else
                tbn = s_diagram;

            if ((grid == 0) || (tabname != tbn)) {
                if (grid != 0) {
                    addTab(grid, tabname);
                    grid->setObjectName(tabname);
                    if (tabname == previous_active_tab)
                        first_visible_page = grid;
                }

                grid = WidgetWithLayout::gridBox(5, this);
                grid->layout()->setMargin(0);
                grid->layout()->setSpacing(0);
                tabname = tbn;
            }

            QGridLayout *gridLayout = (QGridLayout *)grid->layout();
            int currentRow = gridLayout->rowCount();
            //gridLayout->addWidget(new QLabel("", grid), currentRow, 0);
            gridLayout->addWidget(new QLabel(s + " : ", grid), currentRow, 1);
            QWidget * hb = WidgetWithLayout::hBox( grid);
            QHBoxLayout* hLayout;
            hLayout = (QHBoxLayout*)hb->layout();
            hLayout->setMargin(0);
            gridLayout->addWidget(hb,  currentRow, 2);

            ComboStates* widget;
            switch (st.who) {
            case StateSpec::is3states:
                cbstates->insert(i, widget = new ComboStates(hb, *((Uml3States *) st.state), nodefault, unchanged));
                break;

            case StateSpec::isClassDrawingMode:
                cbstates->insert(i, widget = new ComboStates(hb, *((ClassDrawingMode *) st.state),
                                                    nodefault, unchanged));
                break;

            case StateSpec::isDrawingLanguage:
                cbstates->insert(i, widget = new ComboStates(hb, *((DrawingLanguage *) st.state),
                                                    nodefault, unchanged));
                break;

            case StateSpec::isShowContextMode:
                cbstates->insert(i, widget = new ComboStates(hb, *((ShowContextMode *) st.state),
                                                    nodefault, unchanged));
                break;

            default:
                cbstates->insert(i, widget = new ComboStates(hb, *((char *) st.state),
                                                    nodefault, unchanged));
            }
            hLayout->addWidget(widget);
            hLayout->addWidget(new QLabel("", hb));
            gridLayout->addWidget(new QLabel("", grid),currentRow, 3);
            gridLayout->addWidget(new QLabel("", grid),currentRow, 4);
        }

        addTab(grid, tabname);
        grid->setObjectName(tabname);
        if (tabname == previous_active_tab)
            first_visible_page = grid;
    }

    if (colors != 0) {
        QString lbl = QObject::tr("color");
        QString s_default = QObject::tr("default ");

        n = colors->size();
        cbcolors = new QHash<int, ComboColor*>;
        GridBox *gridBox = new GridBox( 5, this);
        gridBox->setMargin(2);
        gridBox->setSpacing(2);

        for (i = 0; i != n; i += 1) {
            if (i == 11) {
                lbl = QObject::tr("color [1]");
                addTab(gridBox, lbl);
                gridBox->setObjectName(lbl);
                if (previous_active_tab == lbl)
                    first_visible_page = gridBox;

                lbl = QObject::tr("color [2]");
                gridBox = new GridBox(5, this);
                gridBox->setMargin(2);
                gridBox->setSpacing(2);
            }

            gridBox->addWidget(new QLabel("", grid));

            QString s = colors->at(i).name;

            s += " : ";
            gridBox->addWidget(new QLabel(s, grid));
            ComboColor *ccolor = new ComboColor(grid, *(colors->at(i).color),nodefault, unchanged);
            gridBox->addWidget(ccolor);
            cbcolors->insert(i, ccolor);
            gridBox->addWidget(new QLabel("", grid));
            gridBox->addWidget(new QLabel("", grid));
        }

        addTab(gridBox, lbl);
        gridBox->setObjectName(lbl);
        if (previous_active_tab == lbl)
            first_visible_page = gridBox;
    }
    setHelpButton(tr("Apply"));
    // use help rather than apply because when the OK button is clicked,
    // the applyButtonPressed() signal is emitted
    setOkButton(tr("OK"));
    setCancelButton(tr("Cancel"));

    connect(this, SIGNAL(helpButtonPressed()),
            this, SLOT(apply()));
    polish();

}

void SettingsDialog::polish()
{

    TabDialog::ensurePolished();
    UmlDesktop::limitsize_center(this, previous_size, 0.8, 0.8);

    if (first_visible_page != 0) {
        move(previous_position);
        previous_active_tab = "";
        showPage(first_visible_page);
    }

}

SettingsDialog::~SettingsDialog()
{
    if (colors != 0)
        delete cbcolors;

    if (states != 0)
        delete cbstates;

    previous_size = size();
}

void SettingsDialog::apply()
{

    did_apply = TRUE;
    previous_position = pos();
    previous_active_tab = m_tabWidget->currentWidget()->objectName();
    accept();

}

void SettingsDialog::accept()
{
    QString s_unchanged = QObject::tr("<unchanged>");
    QString s_default = QObject::tr("default");
    QString s_unlimited = QObject::tr("unlimited");
    unsigned i, n;

    if (states != 0) {
        n = states->size();

        for (i = 0; i != n; i += 1) {
            StateSpec & st = states->at(i);
            QString s = cbstates->value(i)->currentText();

            if (s == s_unchanged)
                st.name = QString();
            else if (st.who == StateSpec::isMemberWidth) {
                if (s == s_default)
                    st.set_state(UmlDefaultMaxMemberWidth);
                else if (s == s_unlimited)
                    st.set_state(UmlUnlimitedMemberWidth);
                else
                    st.set_state(cbstates->value(i)->currentIndex() + MinMemberWidthValue);
            }
            else
                st.set_state(cbstates->value(i)->currentIndex());
        }
    }

    if (colors != 0) {
        n = colors->size();

        for (i = 0; i != n; i += 1) {
            if (cbcolors->value(i)->currentText() == s_unchanged)
                colors->at(i).name = QString();
            else
                *(colors->at(i).color) = (UmlColor) cbcolors->value(i)->currentIndex();
        }
    }

    QDialog::accept();
}
