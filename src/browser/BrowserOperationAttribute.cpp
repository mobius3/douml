#include "browser/BrowserOperationAttribute.h"
#include "browserfunctions/operationfuncs.h"
#include "BrowserView.h"
#include "BrowserClass.h"
#include "OperationData.h"
#include "UmlPixmap.h"

static QStringList DirList;
static void  FIllDirList()
{
    if (DirList.count() == 0)
    {
        // Made DirList without be linked with the items order
        DirList.append(QString());
        DirList.append(QString());
        DirList.append(QString());
        DirList[UmlInOut] = stringify(UmlInOut);
        DirList[UmlIn] = stringify(UmlIn);
        DirList[UmlOut] = stringify(UmlOut);
        // can't be return
    }
}

BrowserOperationAttribute::BrowserOperationAttribute(BrowserView* view, BrowserOperation* _operation, std::shared_ptr<ParamData> _data): BrowserNodeAbstractRemove(view), operation(_operation), param(_data)
{

}

BrowserOperationAttribute::~BrowserOperationAttribute()
{
    set_marked(false);
}

void BrowserOperationAttribute::set_name(QString value)
{
    param->set_name(value);
}

QString BrowserOperationAttribute::get_name() const
{
    return param->get_name();
}

void BrowserOperationAttribute::set_direction(QString value)
{
    FIllDirList();
    UmlParamDirection dir = static_cast<UmlParamDirection>(DirList.indexOf(value));
    param->set_dir(dir);
}

QString BrowserOperationAttribute::get_direction() const
{
    return stringify(param->get_dir());
}

void BrowserOperationAttribute::set_param_type(QString value)
{
    QStringList list;
    BrowserNodeList nodes;
    BrowserClass::instances(nodes);
    nodes.full_names(list);

//    oper->set_param_dir(index, (UmlParamDirection) DirList.findIndex(text(index, 0)));

//    oper->set_param_name(index, text(index, 1).stripWhiteSpace());

    AType t;
    if (!value.isEmpty())
    {
        int rank = list.findIndex(value);

        if (rank != -1)
            t.type = (BrowserClass *) nodes.at(rank);
        else
            t.explicit_type = value;
    }
    param->set_type(t);
}

AType BrowserOperationAttribute::get_param_type() const
{
    return param->get_type();
}

void BrowserOperationAttribute::set_default_value(QString value)
{
    param->set_default_value(value);
}

QString BrowserOperationAttribute::get_default_value() const
{
    return param->get_default_value();
}

void BrowserOperationAttribute::set_passage_type(QString value, int position)
{
    OperationData* data = (OperationData*)operation->get_data();
    data->set_cppdecl(OperationFuncs::set_pointer(position, data->get_cppdecl(), value));
}

QString BrowserOperationAttribute::get_passage_type(int position) const
{
    OperationData* data = (OperationData*)operation->get_data();
    return OperationFuncs::extract_pointer(position, data->get_cppdecl());
}

const QPixmap *BrowserOperationAttribute::pixmap(int) const
{
    if(!isDeleted)
        return PublicAttributeIcon;
    return DeletedAttributeIcon;
}


BrowserOperationReturnType::BrowserOperationReturnType(BrowserView* view, BrowserOperation* _operation): BrowserNodeAbstractRemove(view), operation(_operation)
{
    data = (OperationData*)operation->get_data();
}

void BrowserOperationReturnType::set_param_type(QString value)
{
    QStringList list;
    BrowserNodeList nodes;
    BrowserClass::instances(nodes);
    nodes.full_names(list);

    AType t;
    if (!value.isEmpty())
    {
        int rank = list.findIndex(value);

        if (rank != -1)
            t.type = (BrowserClass *) nodes.at(rank);
        else
            t.explicit_type = value;
    }
    data->set_return_type(t);
}

AType BrowserOperationReturnType::get_param_type() const
{
    return data->get_return_type();
}


BrowserNodeAbstractRemove::BrowserNodeAbstractRemove(BrowserView* view) : BrowserNode(QString(), view)
{
}

uint BrowserOperationAttribute::TypeID()
{
    return TypeIdentifier<BrowserOperationAttribute>::id();
}

bool BrowserOperationAttribute::deletedp() const
{
    return isDeleted;
}

void BrowserOperationAttribute::set_deleted(bool value, int position)
{
    OperationData* data = (OperationData*)operation->get_data();
    if(value)
    {
        data->remove_param(param);
        OperationFuncs::delete_param(position, data);
        isDeleted = true;
    }
    else
    {
        data->insert_param(position, param);
        OperationFuncs::recompute_param(operation, position, true);

        isDeleted = false;
    }

}

QString BrowserOperationAttribute::get_specifier(int position) const
{
    OperationData* data = (OperationData*)operation->get_data();
    return OperationFuncs::extract_specifier(position, data->get_cppdecl());
}

void BrowserOperationAttribute::set_specifier(QString value, int position)
{
    OperationData* data = (OperationData*)operation->get_data();
    data->set_cppdecl(OperationFuncs::set_specifier(position, data->get_cppdecl(), value));
}
