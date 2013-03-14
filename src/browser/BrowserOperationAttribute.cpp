#include "browser/BrowserOperationAttribute.h"
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

void BrowserOperationAttribute::set_direction(QString value)
{
    FIllDirList();
    UmlParamDirection dir = static_cast<UmlParamDirection>(DirList.indexOf(value));
    data->set_dir(dir);
}

QString BrowserOperationAttribute::get_direction() const
{
    return stringify(data->get_dir());
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

void BrowserOperationAttribute::set_passage_type(QString)
{
}

QString BrowserOperationAttribute::get_passage_type() const
{
    return QString();
}

const QPixmap *BrowserOperationAttribute::pixmap(int) const
{
    return PublicAttributeIcon;
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

uint BrowserNodeAbstractRemove::TypeID()
{
   return TypeIdentifier<BrowserNodeAbstractRemove>::id();
}
