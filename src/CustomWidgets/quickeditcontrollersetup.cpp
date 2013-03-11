#include "quickedit.h"


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

static const int nameIndex = 0;
static const int typeIndex = 1;
static const int defaultIndex = 2;
static const int stereotypeIndex = 3;
static const int visibilityIndex = 4;
static const int staticIndex = 5;
static const int abstractIndex = 6;
static const int multiplicityIndex = 7;
static const int directionIndex = 8;

#define ADD_GETSET(TYPE,HOLDER,ROW,ROLES,CONVERTER,ACCESSOR,SETTER)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data) \
{ \
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
    [] (BrowserNode* data, QVariant value) \
{ \
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
    [] (const BrowserNode* data) \
{ \
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
    [] (const BrowserNode* data) \
{ \
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
    [] (BrowserNode* data, QVariant value) \
{ \
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
    [] (const BrowserNode* data) \
{ \
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
    [] (BrowserNode* data, QVariant value) \
{ \
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
    [] (const BrowserNode* data) \
{ \
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
    [] (BrowserNode* data, QVariant value) \
{ \
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
}

// some really insane code from stackoverflow that allows to shorten lengthy ifs
template <typename T0, typename T1, std::size_t N>
bool operator *(const T0& lhs, const std::array<T1, N>& rhs) {
    return std::find(begin(rhs), end(rhs), lhs) != end(rhs);
}

template<class T0, class...T> std::array<T0, 1+sizeof...(T)> in(T0 arg0, T...args) {
    return {{arg0, args...}};
}


#define ADD_GETSET_DATA(TYPE,DATA_TYPE, HOLDER,ROW,ROLES,CONVERTER,ACCESSOR,SETTER)  \
    HOLDER->AddGetter(ROW,ROLES, \
    [] (const BrowserNode* data) \
{ \
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
    [] (BrowserNode* data, QVariant value) \
{ \
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
    ADD_GETSET(BrowserClass, classController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET(BrowserClass, classController, stereotypeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_stereotype, def->set_stereotype);
//    ADD_GETSET(BrowserClass, classController, stereotypeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//               toString, get_stereotype, def->set_stereotype);
//    ADD_GETSET(BrowserClass, classController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//               toInt, def->get_uml_visibility, def->set_uml_visibility);


    ADD_GETSET_CONVERTED(BrowserClass, classController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_uml_visibility);

    ADD_GETSET(BrowserClass, classController, abstractIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toBool, def->get_is_abstract, def->set_is_abstract);

    ADD_PIXMAP_GETTER(BrowserClass, classController, nameIndex,std::initializer_list<int>({Qt::DecorationRole}), pixmap);
//    classController->AddGetter(nameIndex,std::initializer_list<int>({Qt::DecorationRole}),
//    [] (const BrowserNode* data)
//{
//    if(!data)
//    return QVariant();
//    const BrowserClass* pointer = static_cast<const BrowserClass*>(data);
//    if(pointer)
//    {
//        const QPixmap* px = pointer->pixmap(0);
////        QPixmap pxConst = QIcon(":/root/icons/mouse_control.png").pixmap();
////        const QPixmap* px = &pxConst;
//        return QVariant(QIcon(*px));
//    }
//    else
//    return QVariant();
//    }
//    );



    classController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,stereotypeIndex,visibilityIndex,abstractIndex)))
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
    ADD_GETSET(BrowserOperation, operationController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET(BrowserOperationReturnType, operationController, typeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_param_type().get_type, set_param_type);
//    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                    toInt, get_cpp_visibility, set_cpp_visibility);
//    ADD_GETSET_DIRECT_ASSIGNMENT(BrowserOperation, operationController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                                 visibility_as_string(), BrowserNode::encode_visibility(value.toString()));

    ADD_GETSET_CONVERTED(BrowserOperation, operationController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_uml_visibility);

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, staticIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_isa_class_operation, set_isa_class_operation);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, abstractIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_is_abstract, set_is_abstract);

    //data->get_cpp_name_spec();
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("const"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_const, set_cpp_const);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("volatile"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_is_volatile, set_is_volatile);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("friend"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_friend, set_cpp_friend);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("virtual"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_virtual, set_cpp_virtual);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("inline"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_inline, set_cpp_inline);
    //"default" << "delete" <<  "override" <<  "final" <<  "noexcept";

    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("default"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_default, set_cpp_default);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("delete"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_delete, set_cpp_delete);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("override"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_override, set_cpp_override);
    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("final"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_cpp_final, set_cpp_final);
//    ADD_GETSET_DATA(BrowserOperation, OperationData, operationController, columns.indexOf("noexcept"), std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                    toBool,get_cpp_const, set_cpp_const);



    ADD_PIXMAP_GETTER(BrowserOperation, operationController, nameIndex,std::initializer_list<int>({Qt::DecorationRole}), pixmap);


    operationController->AddFlagsFunctor
            (
                [&](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,staticIndex,visibilityIndex,abstractIndex,
                                columns.indexOf("const"), columns.indexOf("volatile"),columns.indexOf("friend"),columns.indexOf("virtual"),columns.indexOf("inline")
                                ,columns.indexOf("default"),columns.indexOf("delete"),columns.indexOf("override"),columns.indexOf("final"))))
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
    ADD_GETSET(BrowserAttribute, attributeController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, typeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toString, get_type().get_type, set_type);
    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, defaultIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toString, get_init_value, set_init_value);
    ADD_GETSET(BrowserAttribute, attributeController, stereotypeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_stereotype, def->set_stereotype);

//    ADD_GETSET_DIRECT_ASSIGNMENT(BrowserAttribute, attributeController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                                 visibility_as_string(), BrowserNode::encode_visibility(value.toString()));
    ADD_GETSET_CONVERTED(BrowserAttribute, attributeController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                         toString,BrowserNode::encode_visibility,visibility_as_string, pointer->def->set_visibility);



    ADD_GETSET_DATA(BrowserAttribute, AttributeData, attributeController, staticIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                    toBool,get_isa_class_attribute, set_isa_class_attribute);





    ADD_PIXMAP_GETTER(BrowserAttribute, attributeController, nameIndex, std::initializer_list<int>({Qt::DecorationRole}), pixmap);

    attributeController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,defaultIndex,stereotypeIndex, visibilityIndex, staticIndex)))
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
}

void QuickEdit::SetupOperationAttributeController()
{
    operationAttributeController = QSharedPointer<ItemController<BrowserNode> >( new ItemController<BrowserNode>());
    operationAttributeController->SetColumns(columns);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, typeIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_param_type().get_type, set_param_type);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, defaultIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_default_value, set_default_value);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, directionIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_direction, set_direction);

    std::function<void(BrowserNode* , const QModelIndex&)> f = [](BrowserNode* node, const QModelIndex& index)
    {
        BrowserOperationAttribute* oper = static_cast<BrowserOperationAttribute*>(node);
        recompute_param(oper->get_operation(),index.row(),true);
    };
    operationAttributeController->AddPostProcessors(directionIndex, QVector<int>(std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole})),f);

    //ADD_PIXMAP_GETTER(BrowserAttribute, attributeController, nameIndex, std::initializer_list<int>({Qt::DecorationRole}), pixmap);

    ADD_PIXMAP_GETTER(BrowserOperationAttribute, operationAttributeController, nameIndex, std::initializer_list<int>({Qt::DecorationRole}), pixmap);



    operationAttributeController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,defaultIndex,directionIndex)))
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

    ADD_GETSET(BrowserRelation, relationController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, defaultIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                      toString, def->a.init_value.operator QString());
//    ADD_GETSET_DIRECT_ASSIGNMENT(BrowserRelation, relationController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                                 visibility_as_string(),  BrowserNode::encode_visibility(value.toString()));
    std::function<void(RoleData& , UmlVisibility ) > f = [](RoleData& data, UmlVisibility vis){data.uml_visibility = vis;};
//    ADD_GETSET_CONVERTED(BrowserRelation, relationController, visibilityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
//                         toString,BrowserNode::encode_visibility,visibility_as_string,  [](RoleData& data, UmlVisibility vis){data.uml_visibility = vis;}(pointer->def->a));
    ADD_PIXMAP_GETTER(BrowserRelation, relationController, nameIndex, std::initializer_list<int>({Qt::DecorationRole}), pixmap);


    relationController->AddGetter(visibilityIndex,std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (const BrowserNode* data)
{
    if(!data)
    return QVariant();
    const BrowserRelation* pointer = static_cast<const BrowserRelation*>(data);
    if(pointer)
    return QVariant(pointer->visibility_as_string());
    else
    return QVariant();
    }
    );
    relationController->AddSetter(visibilityIndex,std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
    [] (BrowserNode* data, QVariant value)
{
    if(!data)
    return false;
    BrowserRelation* pointer = static_cast<BrowserRelation*>(data);
    if(pointer)
        pointer->def->a.uml_visibility = BrowserNode::encode_visibility(value.toString());
    pointer->modified();
    return true;
    }
    );


    ADD_GETSET_DIRECT(BrowserRelation, relationController, staticIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                      toBool, def->a.isa_class_relation);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, multiplicityIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                      toString, def->a.multiplicity.operator QString());

    relationController->AddGetter(typeIndex,std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                                  [] (const BrowserNode* data)
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
    relationController->AddSetter(1,std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
                                  [] (BrowserNode* data, QVariant value)
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
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex,typeIndex,defaultIndex,visibilityIndex)))
            return result;

        TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
        if(!iface)
            return result;
        BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
        if(!pointer)
            return result;
        if(pointer->is_writable() && (index.column() *in(nameIndex,defaultIndex,visibilityIndex)))
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
    ADD_GETSET(BrowserExtraMember, extraNodeController, nameIndex, std::initializer_list<int>({Qt::DisplayRole,Qt::EditRole}),
               toString, get_name, set_name);

    ADD_PIXMAP_GETTER(BrowserExtraMember, extraNodeController, nameIndex, std::initializer_list<int>({Qt::DecorationRole}), pixmap);

    extraNodeController->AddFlagsFunctor
            (
                [](const QModelIndex& index)
    {
        Qt::ItemFlags result;
        result |= Qt::ItemIsSelectable;
        if(!(index.column() *in(nameIndex)))
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



