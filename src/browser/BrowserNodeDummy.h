#ifndef BROWSERNODEDUMMY_H
#define BROWSERNODEDUMMY_H
#include "browser/BrowserNode.h"
class BrowserNodeDummy : public BrowserNode
{
public:
    BrowserNodeDummy(Q3ListView* view): BrowserNode(view){}
    virtual ~BrowserNodeDummy();
    virtual BrowserNode * duplicate(BrowserNode * ,
                                    QString ){return 0;}
    virtual void menu() {}
    virtual void apply_shortcut(QString) {}
    virtual UmlCode get_type() const{return UmlAssociation;}
    virtual QString get_stype() const{return QString();}
    virtual int get_identifier() const{return 0;}
    virtual void save(QTextStream &, bool , QString & ){}
    virtual BasicData * get_data() const {return 0;}
    virtual void prepare_update_lib() const{};

};

#endif // BROWSERNODEDUMMY_H
