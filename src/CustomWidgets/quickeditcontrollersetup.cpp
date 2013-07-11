#include "quickedit.h"

#include "Libs/L_UniversalModels/include/ItemController.h"
#include "Libs/L_UniversalModels/include/TreeModel.h"
#include "Libs/L_UniversalModels/include/TreeItemInterface.h"
#include "Libs/L_UniversalModels/include/treeviewfunctions.h"
#include "Libs/L_UniversalModels/include/treeviewtemplatefunctions.h"
#include "Libs/L_UniversalModels/include/TreeItem.h"
#include "Libs/L_UniversalModels/include/genericeventfilter.h"
#include "browser/BrowserClass.h"
#include "browser/BrowserOperationAttribute.h"
#include "browser/BrowserNodeDummy.h"
#include "browser/BrowserAttribute.h"
#include "tool/snippets.h"
#include "ProfiledStereotypes.h"
#include "browser/BrowserRelation.h"
#include "browser/BrowserExtraMember.h"
#include "AttributeData.h"
#include "BrowserView.h"
#include "AType.h"
#include "UmlEnum.h"
#include "data/ClassData.h"
#include "data/OperationData.h"
#include "data/RelationData.h"
#include "GenericDelegate.h"
#include "browserfunctions/operationfuncs.h"


#include <algorithm>
#include <iostream>
#include <array>
#include <functional>


#define ADD_GETSET(TYPE,HOLDER,ROW,ROLES,CONVERTER,ACCESSOR,SETTER)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(pointer->ACCESSOR()); \
    else \
    return QVariant(); \
    } \
    ); \
    HOLDER->AddSetter(ROW,ROLES, \
    [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
    pointer->SETTER(value.CONVERTER()); \
    pointer->modified();\
    return true;\
    } \
    );

#define ADD_PIXMAP_GETTER(TYPE,HOLDER,ROW,ROLES,ACCESSOR)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(QIcon(*pointer->ACCESSOR(0))); \
    else \
    return QVariant(); \
    } \
    ); \

#define ADD_GETSET_CONVERTED(TYPE,HOLDER,ROW,ROLES,VARIANTCONVERTER, VALUECONVERTER, ACCESSOR,SETTER)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(pointer->ACCESSOR()); \
    else \
    return QVariant(); \
    } \
    ); \
    HOLDER->AddSetter(ROW,ROLES, \
    [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
    SETTER(VALUECONVERTER(value.VARIANTCONVERTER())); \
    pointer->modified();\
    return true;\
    } \
    );

#define ADD_GETSET_DIRECT(TYPE,HOLDER,ROW,ROLES,CONVERTER,PARAM)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(pointer->PARAM); \
    else \
    return QVariant(); \
    } \
    ); \
    HOLDER->AddSetter(ROW,ROLES, \
    [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
    pointer->PARAM  = value.CONVERTER(); \
    pointer->modified();\
    return true;\
    } \
    );

#define ADD_GETSET_DIRECT_ASSIGNMENT(TYPE,HOLDER,ROW,ROLES,PARAM, ASSIGNSTRING)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(pointer->PARAM); \
    else \
    return QVariant(); \
    } \
    ); \
    HOLDER->AddSetter(ROW,ROLES, \
    [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
    pointer->PARAM = ASSIGNSTRING;\
    pointer->modified();\
    return true;\
    } \
    );

void QuickEdit::SetupControllers()
{
    SetupClassController();
    SetupOperationController();
    SetupAttributeController();
    SetupOperationAttributeController();
    SetupRelationController();
    SetupExtraNodeController();
}

void QuickEdit::SetupDelegates()
{
    CheckBoxDelegateSetup();
    VisibilityDelegateSetup();
    TypeDelegateSetup();
    DirectionDelegateSetup();
    PrefixDelegateSetup();
    PostfixDelegateSetup();
}

#define ADD_GETSET_DATA(TYPE,DATA_TYPE, HOLDER,ROW,ROLES,CONVERTER,ACCESSOR,SETTER)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return QVariant(); \
    const TYPE* pointer = static_cast<const TYPE*>(data);\
    if(pointer) \
    return QVariant(((DATA_TYPE*)pointer->get_data())->ACCESSOR()); \
    else \
    return QVariant(); \
    } \
    ); \
    HOLDER->AddSetter(ROW,ROLES, \
    [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
{ \
    Q_UNUSED(index)     \
    if(!data)\
    return false; \
    TYPE* pointer = static_cast<TYPE*>(data);\
    if(pointer) \
    ((DATA_TYPE*)pointer->get_data())->SETTER(value.CONVERTER()); \
    pointer->modified();\
    return true;\
    } \
    );

void QuickEdit::SetupClassController()
{
    classController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    classController->SetColumns(columns);
    ADD_GETSET(BrowserClass, classController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET(BrowserClass, classController, columns.indexOf("stereotype"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_stereotype, def->set_stereotype);

    ADD_GETSET(BrowserClass, classController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

    ADD_GETSET_CONVERTED(BrowserClass, classController, columns.indexOf("visibility"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_uml_visibility);

    ADD_GETSET(BrowserClass, classController, columns.indexOf("abstract"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, def->get_is_abstract, def->set_is_abstract);

    ADD_PIXMAP_GETTER(BrowserClass, classController, columns.indexOf("name"),QVector<int>({Qt::DecorationRole}), pixmap);


    classController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"),columns.indexOf("stereotype"),columns.indexOf("visibility"),columns.indexOf("abstract"), columns.indexOf("deleted"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled;
        return result;
    }
    );
}

void QuickEdit::SetupOperationController()
{
    operationController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    operationController->SetColumns(columns);
    ADD_GETSET(BrowserOperation, operationController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("type"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                   toString, get_return_type().get_type, set_return_type);

    ADD_GETSET_CONVERTED(BrowserOperation, operationController, columns.indexOf("visibility"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_uml_visibility);

    ADD_GETSET(BrowserOperation, operationController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("static"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_isa_class_operation, set_isa_class_operation);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("abstract"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_is_abstract, set_is_abstract);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("const"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_const, set_cpp_const);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("volatile"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_is_volatile, set_is_volatile);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("friend"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_friend, set_cpp_friend);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("virtual"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_virtual, set_cpp_virtual);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("inline"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_inline, set_cpp_inline);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("defaulted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_default, set_cpp_default);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("delete"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_delete, set_cpp_delete);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("override"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_override, set_cpp_override);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("final"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_final, set_cpp_final);

    std::function<void(BrowserNode*,const QModelIndex& index)> f = [](BrowserNode* node ,const QModelIndex& index)
    {
        Q_UNUSED(index);
        BrowserOperation* oper = static_cast<BrowserOperation*>(node);
        oper->modified();
        oper->setText(0,oper->get_name() );
        oper->package_modified();
        oper->get_data()->modified();
    };
    operationController->AddPostProcessors(columns.indexOf("name"), QVector<int>(QVector<int>({Qt::DisplayRole,Qt::EditRole})),f);

    ADD_PIXMAP_GETTER(BrowserOperation, operationController, columns.indexOf("name"),QVector<int>({Qt::DecorationRole}), pixmap);


    operationController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"),columns.indexOf("type"),columns.indexOf("static"),columns.indexOf("visibility"),columns.indexOf("abstract"),
                                columns.indexOf("const"), columns.indexOf("volatile"),columns.indexOf("friend"),columns.indexOf("virtual"),columns.indexOf("inline")
                                ,columns.indexOf("defaulted"),columns.indexOf("delete"),columns.indexOf("override"),columns.indexOf("final"), columns.indexOf("deleted"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserOperation* pointer = static_cast<BrowserOperation*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable() && !((OperationData*)pointer->get_data())->get_or_set())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled;
        return result;
    }
    );
}

void QuickEdit::SetupAttributeController()
{
    attributeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    attributeController->SetColumns(columns);
    ADD_GETSET(BrowserAttribute, attributeController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, columns.indexOf("type"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toString, get_type().get_type, set_type);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, columns.indexOf("default_value"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toString, get_init_value, set_init_value);
    ADD_GETSET(BrowserAttribute, attributeController, columns.indexOf("stereotype"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_stereotype, def->set_stereotype);

    ADD_GETSET(BrowserAttribute, attributeController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

//    ADD_GETSET_DIRECT_ASSIGNMENT(BrowserAttribute, attributeController, columns.indexOf("visibility"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
//                                 visibility_as_string(), BrowserNode::encode_visibility(value.toString()));
    ADD_GETSET_CONVERTED(BrowserAttribute, attributeController, columns.indexOf("visibility"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_visibility);



    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, columns.indexOf("static"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_isa_class_attribute, set_isa_class_attribute);





    ADD_PIXMAP_GETTER(BrowserAttribute, attributeController, columns.indexOf("name"), QVector<int>({Qt::DecorationRole}), pixmap);

    attributeController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"),columns.indexOf("type"),columns.indexOf("default_value"),columns.indexOf("stereotype"),
                                columns.indexOf("visibility"), columns.indexOf("static"), columns.indexOf("deleted"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled ;
        return result;
    }
    );

    std::function<void(BrowserNode*,const QModelIndex& index)> f = [](BrowserNode* node ,const QModelIndex& index)
    {
        Q_UNUSED(index);
        BrowserAttribute* attr = static_cast<BrowserAttribute*>(node);
        attr->modified();
        attr->setText(0,attr->get_name() );
        attr->package_modified();
        attr->get_data()->modified();
    };
    attributeController->AddPostProcessors(columns.indexOf("name"), QVector<int>(QVector<int>({Qt::DisplayRole,Qt::EditRole})),f);
}

void QuickEdit::SetupOperationAttributeController()
{
    operationAttributeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    operationAttributeController->SetColumns(columns);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("type"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_param_type().get_type, set_param_type);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("default_value"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_default_value, set_default_value);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("direction"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_direction, set_direction);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

//    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("prefix"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
//               toString, get_specifier, set_specifier);

    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, columns.indexOf("mark"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, markedp, set_marked);

    operationAttributeController->AddGetter(columns.indexOf("deleted"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (const BrowserNode* data, const QModelIndex& index)
{
        Q_UNUSED(index);
        if(!data)
    return QVariant();
    const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
    if(pointer)
    return QVariant(pointer->deletedp());
    else
    return QVariant();
    }
    );
    operationAttributeController->AddSetter(columns.indexOf("deleted"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (BrowserNode* data, QVariant value, const QModelIndex& index)
 {
    if(!data)
    return false;
    BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
    if(pointer)
    {
        pointer->set_deleted(value.toBool(), index.row());
        pointer->modified();
    }
    return true;
    }
    );

    operationAttributeController->AddGetter(columns.indexOf("prefix"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (const BrowserNode* data, const QModelIndex& index)
{
        Q_UNUSED(index);
        if(!data)
    return QVariant();
    const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
    if(pointer)
        return QVariant(pointer->get_specifier(index.row()));
    else
    return QVariant();
    }
    );
    operationAttributeController->AddSetter(columns.indexOf("prefix"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (BrowserNode* data, QVariant value, const QModelIndex& index)
 {
    if(!data)
    return false;
    BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
    if(pointer)
    {
        pointer->set_specifier(value.toString(), index.row());
        pointer->modified();
    }
    return true;
    }
    );

    operationAttributeController->AddGetter(columns.indexOf("postfix"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (const BrowserNode* data, const QModelIndex& index)
{
        Q_UNUSED(index);
        if(!data)
    return QVariant();
    const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
    if(pointer)
        return QVariant(pointer->get_passage_type(index.row()));
    else
    return QVariant();
    }
    );
    operationAttributeController->AddSetter(columns.indexOf("postfix"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (BrowserNode* data, QVariant value, const QModelIndex& index)
 {
    if(!data)
    return false;
    BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
    if(pointer)
    {
        pointer->set_passage_type(value.toString(), index.row());
        pointer->modified();
    }
    return true;
    }
    );





    std::function<void(BrowserNode* , const QModelIndex&)> f = [](BrowserNode* node, const QModelIndex& index)
    {
        BrowserOperationAttribute* oper = static_cast<BrowserOperationAttribute*>(node);
        OperationFuncs::recompute_param(oper->get_operation(),index.row(),true);
    };
    operationAttributeController->AddPostProcessors(columns.indexOf("direction"), QVector<int>(QVector<int>({Qt::DisplayRole,Qt::EditRole})),f);

    ADD_PIXMAP_GETTER(BrowserOperationAttribute, operationAttributeController, columns.indexOf("name"), QVector<int>({Qt::DecorationRole}), pixmap);



    operationAttributeController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"),columns.indexOf("type"),columns.indexOf("default_value"),
                                columns.indexOf("direction"), columns.indexOf("deleted"), columns.indexOf("mark"),
                                columns.indexOf("prefix"), columns.indexOf("postfix"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(iface->InternalPointer());
        if(!pointer)
            return result;

        if(pointer->is_writable() && !pointer->is_get_set())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled ;
        return result;
    }
    );
}


void QuickEdit::SetupRelationController()
{
    relationController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    relationController->SetColumns(columns);

    ADD_GETSET(BrowserRelation, relationController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, columns.indexOf("default"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                      toString, def->a.init_value.operator QString());

    ADD_GETSET(BrowserRelation, relationController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

    std::function<void(RoleData& , UmlVisibility ) > f = [](RoleData& data, UmlVisibility vis){data.uml_visibility = vis;};

    ADD_PIXMAP_GETTER(BrowserRelation, relationController, columns.indexOf("name"), QVector<int>({Qt::DecorationRole}), pixmap);


    relationController->AddGetter(columns.indexOf("visibility"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (const BrowserNode* data, const QModelIndex& index)
{
    Q_UNUSED(index);
        if(!data)
    return QVariant();
    const BrowserRelation* pointer = static_cast<const BrowserRelation*>(data);
    if(pointer)
    return QVariant(pointer->visibility_as_string());
    else
    return QVariant();
    }
    );
    relationController->AddSetter(columns.indexOf("visibility"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (BrowserNode* data, QVariant value, const QModelIndex& index)
{
    Q_UNUSED(index);
        if(!data)
    return false;
    BrowserRelation* pointer = static_cast<BrowserRelation*>(data);
    if(pointer)
        pointer->def->a.uml_visibility = BrowserNode::encode_visibility(value.toString());
    pointer->modified();
    return true;
    }
    );


    ADD_GETSET_DIRECT(BrowserRelation, relationController, columns.indexOf("static"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                      toBool, def->a.isa_class_relation);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, columns.indexOf("multiplicity"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                      toString, def->a.multiplicity.operator QString());

    relationController->AddGetter(columns.indexOf("type"),QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                                  [] (const BrowserNode* data, const QModelIndex& )
    {

        if(!data)
            return QVariant();
        const BrowserRelation* pointer = static_cast<const BrowserRelation*>(data);
        if(pointer)
            return QVariant(pointer->def->get_end_class()->get_name());
        else
            return QVariant();
    }
    );
    relationController->AddSetter(1,QVector<int>({Qt::DisplayRole,Qt::EditRole}),
                                  [] (BrowserNode* data, QVariant value, const QModelIndex& )
    {
        if(!data)
            return false;
        BrowserRelation* pointer = static_cast<BrowserRelation*>(data);
        if(pointer)
            pointer->def->get_end_class()->set_name(value.toString());
        pointer->modified();
        return true;
    });


    relationController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"),columns.indexOf("type"),columns.indexOf("default"),columns.indexOf("visibility"), columns.indexOf("deleted"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable() && (index.column() *in(columns.indexOf("name"),columns.indexOf("default"),columns.indexOf("visibility"))))
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled ;
        return result;
    }
    );
}

void QuickEdit::SetupExtraNodeController()
{

    extraNodeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    extraNodeController->SetColumns(columns);
    ADD_GETSET(BrowserExtraMember, extraNodeController, columns.indexOf("name"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);

    ADD_GETSET(BrowserExtraMember, extraNodeController, columns.indexOf("deleted"), QVector<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, deletedp, set_deleted);

    ADD_PIXMAP_GETTER(BrowserExtraMember, extraNodeController, columns.indexOf("name"), QVector<int>({Qt::DecorationRole}), pixmap);

    extraNodeController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(columns.indexOf("name"), columns.indexOf("deleted"))))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable())
            result |= Qt::ItemIsEditable;
        result |=  Qt::ItemIsEnabled;
        return result;
    }
    );
}



