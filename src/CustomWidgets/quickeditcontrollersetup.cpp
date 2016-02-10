// *************************************************************************
//
//
//
// This file is part of the Douml Uml Toolkit.
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
//
// *************************************************************************

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

// Helper macros

#define ADD_GETSET(TYPE, HOLDER, ROW, ROLES, CONVERTER, ACCESSOR, SETTER) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [](const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(pointer->ACCESSOR()); \
            else \
                return QVariant(); \
        } \
        ); \
    HOLDER->AddSetter(columns.indexOf(ROW), ROLES, \
        [](BrowserNode* data, QVariant value, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return false; \
            TYPE* pointer = static_cast<TYPE*>(data); \
            if (pointer) \
                pointer->SETTER(value.CONVERTER()); \
            pointer->modified(); \
            return true; \
        } \
        );

#define ADD_PIXMAP_GETTER(TYPE, HOLDER, ROW, ROLES, ACCESSOR) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [](const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(QIcon(*pointer->ACCESSOR(0))); \
            else \
                return QVariant(); \
        } \
        ); \

#define ADD_GETSET_CONVERTED(TYPE, HOLDER, ROW, ROLES, VARIANTCONVERTER, VALUECONVERTER, ACCESSOR, SETTER) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [](const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(pointer->ACCESSOR()); \
            else \
                return QVariant(); \
        } \
        ); \
    HOLDER->AddSetter(columns.indexOf(ROW), ROLES, \
        [](BrowserNode* data, QVariant value, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data)\
                return false; \
            TYPE* pointer = static_cast<TYPE*>(data);\
            if (pointer) \
                SETTER(VALUECONVERTER(value.VARIANTCONVERTER())); \
            pointer->modified();\
            return true;\
        } \
        );

#define ADD_GETSET_DIRECT(TYPE, HOLDER, ROW, ROLES, CONVERTER, PARAM) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [](const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(pointer->PARAM); \
            else \
                return QVariant(); \
        } \
        ); \
    HOLDER->AddSetter(columns.indexOf(ROW), ROLES, \
        [](BrowserNode* data, QVariant value, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return false; \
            TYPE* pointer = static_cast<TYPE*>(data); \
            if (pointer) \
                pointer->PARAM = value.CONVERTER(); \
            pointer->modified(); \
            return true;\
        } \
        );

#define ADD_GETSET_DIRECT_ASSIGNMENT(TYPE, HOLDER, ROW, ROLES, PARAM, ASSIGNSTRING) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [](const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(pointer->PARAM); \
            else \
                return QVariant(); \
        } \
        ); \
    HOLDER->AddSetter(columns.indexOf(ROW), ROLES, \
        [](BrowserNode* data, QVariant value, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return false; \
            TYPE* pointer = static_cast<TYPE*>(data); \
            if (pointer) \
                pointer->PARAM = ASSIGNSTRING; \
            pointer->modified(); \
            return true; \
        } \
        );

#define ADD_GETSET_DATA(TYPE, DATA_TYPE, HOLDER, ROW, ROLES, CONVERTER, ACCESSOR, SETTER) \
    HOLDER->AddGetter(columns.indexOf(ROW), ROLES, \
        [] (const BrowserNode* data, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return QVariant(); \
            const TYPE* pointer = static_cast<const TYPE*>(data); \
            if (pointer) \
                return QVariant(((DATA_TYPE*)pointer->get_data())->ACCESSOR()); \
            else \
                return QVariant(); \
        } \
        ); \
    HOLDER->AddSetter(columns.indexOf(ROW), ROLES, \
        [] (BrowserNode* data, QVariant value, const QModelIndex& index) \
        { \
            Q_UNUSED(index) \
            if (!data) \
                return false; \
            TYPE* pointer = static_cast<TYPE*>(data); \
            if (pointer) \
                ((DATA_TYPE*)pointer->get_data())->SETTER(value.CONVERTER()); \
            pointer->modified(); \
            return true;\
        } \
        );

// Display and Edit roles
static const auto rolesEdit = QVector<int>({Qt::DisplayRole,Qt::EditRole});
// Decoration role
static const auto rolesDeco = QVector<int>({Qt::DecorationRole});

/*!
 Set up the quick edit view for all types of items.
 */
void QuickEdit::SetupControllers()
{
    SetupClassController();
    SetupOperationController();
    SetupAttributeController();
    SetupOperationAttributeController();
    SetupRelationController();
    SetupExtraNodeController();
}

/*!
 Set up all the quick edit view's delegates/
 */
void QuickEdit::SetupDelegates()
{
    CheckBoxDelegateSetup();
    VisibilityDelegateSetup();
    TypeDelegateSetup();
    DirectionDelegateSetup();
    PrefixDelegateSetup();
    PostfixDelegateSetup();
}

/*!
 Sets the quick edit view for Class items.
 */
void QuickEdit::SetupClassController()
{
    classController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    classController->SetColumns(columns);

    ADD_GETSET(          BrowserClass, classController, "name",       rolesEdit, toString, get_name,                       set_name);
    ADD_GETSET(          BrowserClass, classController, "stereotype", rolesEdit, toString, get_stereotype,                 def->set_stereotype);
    ADD_GETSET(          BrowserClass, classController, "deleted",    rolesEdit, toBool,   deletedp,                       set_deleted);
    ADD_GETSET_CONVERTED(BrowserClass, classController, "visibility", rolesEdit, toString, BrowserNode::encode_visibility, visibility_as_string, pointer->def->set_uml_visibility);
    ADD_GETSET(          BrowserClass, classController, "abstract",   rolesEdit, toBool,   def->get_is_abstract,           def->set_is_abstract);

    ADD_PIXMAP_GETTER(BrowserClass, classController, "name", rolesDeco, pixmap);

    classController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
            Qt::ItemFlags result;
            result |= Qt::ItemIsSelectable;
            if (!(index.column() * in(columns.indexOf("name"),
                                      columns.indexOf("stereotype"),
                                      columns.indexOf("visibility"),
                                      columns.indexOf("abstract"),
                                      columns.indexOf("deleted")))) {
                return result;
            }
            TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
            if (!iface)
                return result;
            BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
            if (!pointer)
                return result;
            if (pointer->is_writable()) {
                result |= Qt::ItemIsEditable;
            }
            result |=  Qt::ItemIsEnabled;
            return result;
        }
    );
}

/*!
 Sets the quick edit view for Operation items.
 */
void QuickEdit::SetupOperationController()
{
    operationController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    operationController->SetColumns(columns);

    ADD_GETSET(          BrowserOperation, operationController,                "name",       rolesEdit, toString().toLatin1().constData, get_name,                       set_name);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "type",       rolesEdit, toString,                        get_return_type().get_type,     set_return_type);
    ADD_GETSET_CONVERTED(BrowserOperation, operationController,                "visibility", rolesEdit, toString,                        BrowserNode::encode_visibility, visibility_as_string, pointer->def->set_uml_visibility);
    ADD_GETSET(          BrowserOperation, operationController,                "deleted",    rolesEdit, toBool,                          deletedp,                       set_deleted);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "static",     rolesEdit, toBool,                          get_isa_class_operation,        set_isa_class_operation);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "abstract",   rolesEdit, toBool,                          get_is_abstract,                set_is_abstract);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "const",      rolesEdit, toBool,                          get_cpp_const,                  set_cpp_const);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "volatile",   rolesEdit, toBool,                          get_is_volatile,                set_is_volatile);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "friend",     rolesEdit, toBool,                          get_cpp_friend,                 set_cpp_friend);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "virtual",    rolesEdit, toBool,                          get_cpp_virtual,                set_cpp_virtual);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "inline",     rolesEdit, toBool,                          get_cpp_inline,                 set_cpp_inline);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "defaulted",  rolesEdit, toBool,                          get_cpp_default,                set_cpp_default);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "delete",     rolesEdit, toBool,                          get_cpp_delete,                 set_cpp_delete);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "override",   rolesEdit, toBool,                          get_cpp_override,               set_cpp_override);
    ADD_GETSET_DATA(     BrowserOperation, OperationData, operationController, "final",      rolesEdit, toBool,                          get_cpp_final,                  set_cpp_final);

    // post processors
    operationController->AddPostProcessors(
        columns.indexOf("name"),
        QVector<int>(rolesEdit),
        [](BrowserNode* node, const QModelIndex& index)
        {
            Q_UNUSED(index);
            BrowserOperation* oper = static_cast<BrowserOperation*>(node);
            oper->modified();
            oper->setText(0, oper->get_name());
            oper->package_modified();
            oper->get_data()->modified();
        }
    );

    // pixmap getter
    ADD_PIXMAP_GETTER(BrowserOperation, operationController, "name", rolesDeco, pixmap);

    // flags functors
    operationController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
            Qt::ItemFlags result;
            result |= Qt::ItemIsSelectable;
            if (!(index.column() * in(columns.indexOf("name"),
                                      columns.indexOf("type"),
                                      columns.indexOf("static"),
                                      columns.indexOf("visibility"),
                                      columns.indexOf("abstract"),
                                      columns.indexOf("const"),
                                      columns.indexOf("volatile"),
                                      columns.indexOf("friend"),
                                      columns.indexOf("virtual"),
                                      columns.indexOf("inline"),
                                      columns.indexOf("defaulted"),
                                      columns.indexOf("delete"),
                                      columns.indexOf("override"),
                                      columns.indexOf("final"),
                                      columns.indexOf("deleted")))) {
                return result;
            }
            TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
            if (!iface)
                return result;
            BrowserOperation* pointer = static_cast<BrowserOperation*>(iface->InternalPointer());
            if (!pointer)
                return result;
            if (pointer->is_writable() && !((OperationData*)pointer->get_data())->get_or_set()) {
                result |= Qt::ItemIsEditable;
            }
            result |=  Qt::ItemIsEnabled;
            return result;
        }
    );
}

/*!
 Sets the quick edit view for the Attribute items.
 */
void QuickEdit::SetupAttributeController()
{
    attributeController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    attributeController->SetColumns(columns);

    ADD_GETSET(          BrowserAttribute, attributeController,                "name",          rolesEdit, toString, get_name,                       set_name);
    ADD_GETSET_DATA(     BrowserAttribute, AttributeData, attributeController, "type",          rolesEdit, toString, get_type().get_type,            set_type);
    ADD_GETSET_DATA(     BrowserAttribute, AttributeData, attributeController, "default_value", rolesEdit, toString, get_init_value,                 set_init_value);
    ADD_GETSET(          BrowserAttribute, attributeController,                "stereotype",    rolesEdit, toString, get_stereotype,                 def->set_stereotype);
    ADD_GETSET(          BrowserAttribute, attributeController,                "deleted",       rolesEdit, toBool,   deletedp,                       set_deleted);
    ADD_GETSET_CONVERTED(BrowserAttribute, attributeController,                "visibility",    rolesEdit, toString, BrowserNode::encode_visibility, visibility_as_string, pointer->def->set_visibility);
    ADD_GETSET_DATA(     BrowserAttribute, AttributeData, attributeController, "static",        rolesEdit, toBool,   get_isa_class_attribute,        set_isa_class_attribute);
    ADD_PIXMAP_GETTER(   BrowserAttribute, attributeController,                "name",          rolesDeco, pixmap);

    attributeController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
            Qt::ItemFlags result;
            result |= Qt::ItemIsSelectable;
            if (!(index.column() * in(columns.indexOf("name"),
                                      columns.indexOf("type"),
                                      columns.indexOf("default_value"),
                                      columns.indexOf("stereotype"),
                                      columns.indexOf("visibility"),
                                      columns.indexOf("static"),
                                      columns.indexOf("deleted")))) {
                return result;
            }

            TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
            if (!iface)
                return result;
            BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
            if (!pointer)
                return result;

            if (pointer->is_writable())
                result |= Qt::ItemIsEditable;

            result |= Qt::ItemIsEnabled;

            return result;
        }
    );

    attributeController->AddPostProcessors(
        columns.indexOf("name"),
        QVector<int>(rolesEdit),
        [](BrowserNode* node ,const QModelIndex& index)
        {
            Q_UNUSED(index);
            BrowserAttribute* attr = static_cast<BrowserAttribute*>(node);
            attr->modified();
            attr->setText(0,attr->get_name() );
            attr->package_modified();
            attr->get_data()->modified();
        }
    );
}

/*!
 Sets the quick edit view for the Operation Attribute items.
 */
void QuickEdit::SetupOperationAttributeController()
{
    operationAttributeController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    operationAttributeController->SetColumns(columns);

    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, "name",          rolesEdit, toString, get_name,                  set_name);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, "type",          rolesEdit, toString, get_param_type().get_type, set_param_type);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, "default_value", rolesEdit, toString, get_default_value,         set_default_value);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, "direction",     rolesEdit, toString, get_direction,             set_direction);
    ADD_GETSET(BrowserOperationAttribute, operationAttributeController, "mark",          rolesEdit, toBool,   markedp,                   set_marked);

    operationAttributeController->AddGetter(
        columns.indexOf("deleted"),
        rolesEdit,
        [](const BrowserNode* data, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return QVariant();
            const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
            if (pointer)
                return QVariant(pointer->deletedp());
            else
                return QVariant();
        }
    );

    operationAttributeController->AddSetter(
        columns.indexOf("deleted"),
        rolesEdit,
        [](BrowserNode* data, QVariant value, const QModelIndex& index)
        {
            if (!data)
                return false;
            BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
            if (pointer) {
                pointer->set_deleted(value.toBool(), index.row());
                pointer->modified();
            }
            return true;
        }
    );

    operationAttributeController->AddGetter(
        columns.indexOf("prefix"),
        rolesEdit,
        [](const BrowserNode* data, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return QVariant();
            const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
            if (pointer)
                return QVariant(pointer->get_specifier(index.row()));
            else
                return QVariant();
        }
    );

    operationAttributeController->AddSetter(
        columns.indexOf("prefix"),
        rolesEdit,
        [](BrowserNode* data, QVariant value, const QModelIndex& index)
        {
            if (!data)
                return false;
            BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
            if (pointer) {
                pointer->set_specifier(value.toString(), index.row());
                pointer->modified();
            }
            return true;
        }
    );

    operationAttributeController->AddGetter(
        columns.indexOf("postfix"),
        rolesEdit,
        [](const BrowserNode* data, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return QVariant();
            const BrowserOperationAttribute* pointer = static_cast<const BrowserOperationAttribute*>(data);
            if (pointer)
                return QVariant(pointer->get_passage_type(index.row()));
            else
                return QVariant();
        }
    );

    operationAttributeController->AddSetter(
        columns.indexOf("postfix"),
        rolesEdit,
        [](BrowserNode* data, QVariant value, const QModelIndex& index)
        {
            if (!data)
                return false;
            BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(data);
            if (pointer) {
                pointer->set_passage_type(value.toString(), index.row());
                pointer->modified();
            }
            return true;
        }
    );

    operationAttributeController->AddPostProcessors(
        columns.indexOf("direction"),
        QVector<int>(rolesEdit),
        [](BrowserNode* node, const QModelIndex& index)
        {
            BrowserOperationAttribute* oper = static_cast<BrowserOperationAttribute*>(node);
            OperationFuncs::recompute_param(oper->get_operation(), index.row(), true);
        }
    );

    ADD_PIXMAP_GETTER(BrowserOperationAttribute, operationAttributeController, "name", rolesDeco, pixmap);

    operationAttributeController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
            Qt::ItemFlags result;
            result |= Qt::ItemIsSelectable;
            if (!(index.column() * in(columns.indexOf("name"),
                                      columns.indexOf("type"),
                                      columns.indexOf("default_value"),
                                      columns.indexOf("direction"),
                                      columns.indexOf("deleted"),
                                      columns.indexOf("mark"),
                                      columns.indexOf("prefix"),
                                      columns.indexOf("postfix")))) {
                return result;
            }

            TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
            if(!iface)
                return result;
            BrowserOperationAttribute* pointer = static_cast<BrowserOperationAttribute*>(iface->InternalPointer());
            if(!pointer)
                return result;

            if(pointer->is_writable() && !pointer->is_get_set()) {
                result |= Qt::ItemIsEditable;
            }
            result |=  Qt::ItemIsEnabled ;
            return result;
        }
    );
}

/*!
 Sets the quick edit view for the Relation items.
 */
void QuickEdit::SetupRelationController()
{
    relationController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    relationController->SetColumns(columns);

    ADD_GETSET(       BrowserRelation, relationController, "name",    rolesEdit, toString, get_name, set_name);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, "default", rolesEdit, toString, def->a.init_value.operator QString());
    ADD_GETSET(       BrowserRelation, relationController, "deleted", rolesEdit, toBool,   deletedp, set_deleted);

    ADD_PIXMAP_GETTER(BrowserRelation, relationController, "name", rolesDeco, pixmap);

    relationController->AddGetter(
        columns.indexOf("visibility"),
        rolesEdit,
        [](const BrowserNode* data, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return QVariant();
            const BrowserRelation* pointer = static_cast<const BrowserRelation*>(data);
            if (pointer)
                return QVariant(pointer->visibility_as_string());
            else
                return QVariant();
        }
    );

    relationController->AddSetter(
        columns.indexOf("visibility"),
        rolesEdit,
        [](BrowserNode* data, QVariant value, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return false;
            BrowserRelation* pointer = static_cast<BrowserRelation*>(data);
            if (pointer) {
                pointer->def->a.uml_visibility = BrowserNode::encode_visibility(value.toString());
            }
            pointer->modified();
            return true;
        }
    );

    ADD_GETSET_DIRECT(BrowserRelation, relationController, "static",       rolesEdit, toBool,   def->a.isa_class_relation);
    ADD_GETSET_DIRECT(BrowserRelation, relationController, "multiplicity", rolesEdit, toString, def->a.multiplicity.operator QString());

    relationController->AddGetter(
        columns.indexOf("type"),
        rolesEdit,
        [](const BrowserNode* data, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return QVariant();
            const BrowserRelation* pointer = static_cast<const BrowserRelation*>(data);
            if (pointer)
                return QVariant(pointer->def->get_end_class()->get_name());
            else
                return QVariant();
        }
    );

    relationController->AddSetter(
        1,
        rolesEdit,
        [](BrowserNode* data, QVariant value, const QModelIndex& index)
        {
            Q_UNUSED(index);
            if (!data)
                return false;
            BrowserRelation* pointer = static_cast<BrowserRelation*>(data);
            if (pointer)
                pointer->def->get_end_class()->set_name(value.toString());

            pointer->modified();
            return true;
        }
    );

    relationController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
            Qt::ItemFlags result;

            result |= Qt::ItemIsSelectable;

            if (!(index.column() * in(columns.indexOf("name"),
                                      columns.indexOf("type"),
                                      columns.indexOf("default"),
                                      columns.indexOf("visibility"),
                                      columns.indexOf("deleted")))) {
                return result;
            }

            TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
            if (!iface)
                return result;
            BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
            if (!pointer)
                return result;

            if (pointer->is_writable() &&
                (index.column() * in(columns.indexOf("name"),
                                     columns.indexOf("default"),
                                     columns.indexOf("visibility")))) {
                result |= Qt::ItemIsEditable;
            }

            result |= Qt::ItemIsEnabled;

            return result;
        }
    );
}

/*!
 Sets the quick edit view for the Extra Member items.
 */
void QuickEdit::SetupExtraNodeController()
{
    extraNodeController = QSharedPointer<ItemController<BrowserNode>>(new ItemController<BrowserNode>());
    extraNodeController->SetColumns(columns);

    ADD_GETSET(       BrowserExtraMember, extraNodeController, "name",    rolesEdit, toString().toLatin1().constData, get_name, set_name);
    ADD_GETSET(       BrowserExtraMember, extraNodeController, "deleted", rolesEdit, toBool, deletedp, set_deleted);
    ADD_PIXMAP_GETTER(BrowserExtraMember, extraNodeController, "name",    rolesDeco, pixmap);

    extraNodeController->AddFlagsFunctor(
        [this](const QModelIndex& index)
        {
             Qt::ItemFlags result;
             result |= Qt::ItemIsSelectable;
             if (!(index.column() * in(columns.indexOf("name"),
                                       columns.indexOf("deleted")))) {
                 return result;
             }

             TreeItemInterface* iface = static_cast<TreeItemInterface*>(index.internalPointer());
             if (!iface)
                 return result;
             BrowserNode* pointer = static_cast<BrowserNode*>(iface->InternalPointer());
             if (!pointer)
                 return result;

             if (pointer->is_writable())
                 result |= Qt::ItemIsEditable;

             result |=  Qt::ItemIsEnabled;

             return result;
        }
    );
}
