#ifndef BROWSEROPERATIONATTRIBUTE_H
#define BROWSEROPERATIONATTRIBUTE_H
#include "BrowserNode.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "ParamData.h"
#include "Labeled.h"

class BrowserView;

class BrowserNodeAbstractRemove : public BrowserNode
{

protected:
    BrowserNodeAbstractRemove(BrowserView* view);
    virtual BrowserNode * duplicate(BrowserNode * , const QString &) override {return 0;}
    virtual void prepare_update_lib() const override {}
    virtual void menu() override {}
    virtual void apply_shortcut(const QString &) override {}
    virtual UmlCode get_type() const override {return UmlAssociation;}
    virtual QString get_stype() const override {return QString();}
    virtual int get_identifier() const override {return -1;}
    virtual BasicData * get_data() const override {return 0;}
    virtual void save(QTextStream &, bool , QString & ) override {}
    virtual const QPixmap * pixmap(int) const override {return NULL;}
};


class BrowserOperationAttribute: public BrowserNodeAbstractRemove
{
    BrowserOperation* operation = nullptr;
    std::shared_ptr<ParamData> param;

public:
    BrowserOperationAttribute(BrowserView* view, BrowserOperation* _operation, std::shared_ptr<ParamData> _data);
    ~BrowserOperationAttribute();
    BrowserOperation* get_operation() {return operation;}
    virtual void set_name(const QString &) override;
    virtual QString get_name() const override;
    void set_direction(const QString &);
    QString get_direction() const;
    void set_param_type(const QString &);
    AType get_param_type() const;
    void set_default_value(const QString &);
    QString get_default_value() const;

    virtual bool is_writable() const override
    {
        if(operation)
            return operation->is_writable();
        return false;
    }
    bool is_get_set()
    {
        return ((OperationData*)operation->get_data())->get_or_set();
    }
    virtual void modified() override {operation->package_modified();}
    virtual const QPixmap * pixmap(int) const override;
    virtual uint TypeID() override;
    bool deletedp() const;
    void set_deleted(bool, int position = 0);
    std::shared_ptr<ParamData> get_param() {return param;}

    QString get_specifier(int position) const;
    void set_specifier(const QString & value, int position);
    void set_passage_type(const QString &, int position);
    QString get_passage_type(int position) const;

    bool isDeleted = false;
};

class BrowserOperationReturnType: public BrowserNodeAbstractRemove
{
    BrowserOperation* operation = nullptr;
    OperationData* data;
public:
    BrowserOperationReturnType(BrowserView* view, BrowserOperation* _operation);
    void set_param_type(const QString &);
    AType get_param_type() const;
};

#endif // BROWSEROPERATIONATTRIBUTE_H
