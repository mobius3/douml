//Added by qt3to4:
#include <QPixmap>
#include <QDropEvent>
#include <QTextStream>
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

#ifndef BROWSER_RELATION_H
#define BROWSER_RELATION_H

template <class K> class Q3PtrDict;

class QPixmap;
class BrowserClass;
class RelationData;
class BrowserOperation;

#include "BrowserNode.h"
#include "Labeled.h"

class BrowserRelation : public BrowserNode, public Labeled<BrowserRelation>
{
friend class QuickEdit;
protected:
    static IdDict<BrowserRelation> all;

    RelationData * def;
    BrowserOperation * get_oper;
    BrowserOperation * set_oper;

    BrowserRelation(int id);

    void exec_menu_choice(int rank);

public:
    BrowserRelation(BrowserNode * p, RelationData * d, int id = 0);
    BrowserRelation(const BrowserRelation * model, BrowserNode * p);
    virtual ~BrowserRelation();

    virtual bool is_undefined() const override;

    virtual void delete_it() override;
    virtual bool undelete(bool rec, QString & warning, QString & renamed) override;
    virtual BrowserNode * duplicate(BrowserNode * p,
                                    const QString & name = QString()) override;

    virtual const char * get_comment() const override;
    virtual void set_comment(const QString & c) override;

    virtual UmlVisibility get_visibility() const override;

    BrowserOperation * get_get_oper() {
        return get_oper;
    };
    BrowserOperation * get_set_oper() {
        return set_oper;
    };
    void set_get_oper(BrowserOperation *);
    void set_set_oper(BrowserOperation *);
    void update_get_oper();
    void update_set_oper();
    void add_get_oper();
    void add_set_oper();

    virtual const QPixmap * pixmap(int) const;
    virtual void paintCell(QPainter *, const QPalette &, int, int, int);
    BrowserNode * extract();
    static BrowserRelation * reinsert(BrowserNode * p, RelationData * d);

    virtual void menu() override;
    virtual void apply_shortcut(const QString & s) override;
    virtual void open(bool) override;
    virtual bool in_edition() const override;
    virtual UmlCode get_type() const override;
    virtual QString get_stype() const override;
    virtual int get_identifier() const override;
    virtual const char * help_topic() const override;
    virtual void modified() override;
    virtual BasicData * get_data() const override;
    virtual bool same_name(const QString & s, UmlCode type) const override;
    virtual QString full_name(bool rev = FALSE, bool itself = TRUE) const override;
    virtual void member_cpp_def(const QString & prefix, const QString &,
                                QString & s, bool templ) const override;
    virtual void update_stereotype(bool = FALSE) override;
    virtual QString stereotypes_properties() const override;
    virtual AType class_association() const override;
    virtual const char * constraint() const override;

    virtual void write_id(ToolCom * com) override;
    virtual void save(QTextStream &, bool ref, QString & warning) override;
    static BrowserRelation * read(char *& , char *, BrowserNode *, bool force = TRUE);
    static BrowserRelation * read_ref(char *& st);
    static BrowserRelation * read_ref(char *& , char * k);
    static BrowserRelation * temporary(RelationData * d);
    static BrowserNode * get_it(const char * k, int id);
    static void post_load();
    void invalidate();

    static void clear(bool old);
    static void update_idmax_for_root();
    virtual void renumber(int phase) override;
    virtual void prepare_update_lib() const override;

    virtual void referenced_by(QList<BrowserNode *> &, bool ondelete = FALSE) override;
    static void compute_referenced_by(QList<BrowserNode *> &, BrowserClass *);

    virtual bool tool_cmd(ToolCom * com, const char * args) override;

    static QString drag_key(BrowserNode * p);
    virtual QString drag_key() const override;
    virtual QString drag_postfix() const override;
    virtual void DropAfterEvent(QDropEvent * e, BrowserNode * after) override;

    static void get_relating(BrowserNode *, QHash<BrowserNode *, BrowserNode *> &d,
                             BrowserNodeList & newones,
                             bool inh, bool dep, bool assoc);
    virtual QVariant data(int column, int role) const override;
};

#endif

