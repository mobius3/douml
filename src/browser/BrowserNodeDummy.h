#ifndef BROWSERNODEDUMMY_H
#define BROWSERNODEDUMMY_H

#include "browser/BrowserNode.h"

class BrowserNodeDummy : public BrowserNode
{
public:
    BrowserNodeDummy(BrowserView* view) : BrowserNode(view) {}
    virtual ~BrowserNodeDummy();
    virtual BrowserNode * duplicate(BrowserNode *,
                                    const QString &) override {return 0;}
    virtual void menu() override {}
    virtual void apply_shortcut(const QString &) override {}
    virtual UmlCode get_type() const override {return UmlAssociation;}
    virtual QString get_stype() const override {return QString();}
    virtual int get_identifier() const override {return 0;}
    virtual void save(QTextStream &, bool, QString &) override {}
    virtual BasicData * get_data() const override {return 0;}
    virtual void prepare_update_lib() const override {}
    virtual const QPixmap * pixmap(int) const override {return 0;}
};

#endif // BROWSERNODEDUMMY_H
