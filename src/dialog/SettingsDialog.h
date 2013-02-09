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

#ifndef DEFAULTSDIALOG_H
#define DEFAULTSDIALOG_H

#include <q3tabdialog.h>
#include <q3memarray.h>
#include <q3ptrvector.h>

#include "StateSpec.h"
#include <q3ptrvector.h>

class ComboStates;
class ComboColor;

class ColorSpec
{
public:
    QString name;
    UmlColor * color;

    void set(QString n, UmlColor * c) {
        name = n;
        color = c;
    }
};

class ColorSpecVector
{
public:
    ColorSpecVector(int s) : _size(s) {
        _v = new ColorSpec[s];
    };
    virtual ~ColorSpecVector() {
        if (_v) delete [] _v;
    }
    int size() const {
        return _size;
    }
    void resize(int s);
    ColorSpec & operator[](int i) const {
        return _v[i];
    }
    ColorSpec & at(int i) const {
        return _v[i];
    }

private:
    int _size;
    ColorSpec * _v;
};

class SettingsDialog : public Q3TabDialog
{
    Q_OBJECT

protected:
    StateSpecVector * states;
    ColorSpecVector * colors;
    Q3PtrVector<ComboStates> * cbstates;
    Q3PtrVector<ComboColor> * cbcolors;
    QWidget * first_visible_page;
    bool several;
    bool did_apply;

    static QSize previous_size;
    static QPoint previous_position;
    static QString previous_active_tab;

public:
    SettingsDialog(StateSpecVector * st, ColorSpecVector * co,
                   bool nodefault, bool unchanged = FALSE,
                   QString title = QString());
    virtual ~SettingsDialog();
    bool redo() const {
        return did_apply;
    }

protected slots:
    virtual void polish();
    virtual void accept();
    void apply();
};

#endif
