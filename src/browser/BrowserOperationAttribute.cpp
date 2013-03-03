#include "browser/BrowserOperationAttribute.h"
#include "BrowserView.h"
#include "BrowserClass.h"
#include "OperationData.h"

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

BrowserOperationAttribute::BrowserOperationAttribute(BrowserView* view, BrowserOperation* _operation, ParamData* _data): BrowserNodeAbstractRemove(view), operation(_operation), data(_data)
{

}

void BrowserOperationAttribute::set_name(QString value)
{
    data->set_name(value);
}

QString BrowserOperationAttribute::get_name() const
{
    return data->get_name();
}

void BrowserOperationAttribute::set_direction(UmlParamDirection value)
{
    data->set_dir(value);
}

UmlParamDirection BrowserOperationAttribute::get_direction() const
{
    return data->get_dir();
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
    data->set_type(t);
}

AType BrowserOperationAttribute::get_param_type() const
{
    return data->get_type();
}

void BrowserOperationAttribute::set_default_value(QString value)
{
    data->set_default_value(value);
}

QString BrowserOperationAttribute::get_default_value() const
{
    return data->get_default_value();
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
