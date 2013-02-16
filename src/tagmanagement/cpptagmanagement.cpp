// *************************************************************************
//
// Copyright 2012-2013 Nikolai Marchenko.
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

#include <q3ptrdict.h>
//Added by qt3to4:
#include <functional>
#include <QRegExp>
#include "BrowserOperation.h"
#include "BrowserAttribute.h"
#include "BrowserRelation.h"
#include "BrowserClass.h"
#include "BrowserView.h"
#include "OperationData.h"
#include "ClassData.h"
#include "GenerationSettings.h"
#include "UmlGlobal.h"
#include "DialogUtil.h"
#include "myio.h"
#include "ToolCom.h"
#include "Tool.h"
#include "strutil.h"
#include "ProfiledStereotypes.h"
#include "mu.h"
#include "translate.h"
#include "cpptagmanagement.h"

namespace TagManagers
{
namespace  Cpp
{
void Comment(TagTempStructure& updateData, QString commentText, bool re_template, QString templates)
{
    if (!manage_comment(commentText, updateData.p, updateData.pp,
                        GenerationSettings::cpp_javadoc_style())
            && re_template)
        updateData.s += templates;
}
void Description(TagTempStructure& updateData, QString commentText, bool re_template, QString templates)
{
    if (!manage_description(commentText, updateData.p, updateData.pp) && re_template)
        updateData.s += templates;
}
void HashSymbol(TagTempStructure& updateData)
{
    updateData.s += updateData.indent;
}
bool NullValue(TagTempStructure& updateData, bool re_template, QString templates, QString indent)
{

    if (*updateData.p == 0)
    {
        if (updateData.pp == 0)
            return false;
        // comment management done
        updateData.p = updateData.pp;
        updateData.pp = 0;

        if (re_template)
            updateData.s += templates;

        if (*updateData.p == 0)
            return false;

        if (*updateData.p != '#')
            updateData.s += indent;
    }
    return true;
}
void ReturnType(TagTempStructure& updateData, QString type, QStringList list, BrowserNodeList& nodes)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    updateData.s += get_cpp_name(the_type(type, list, nodes));
}
void Class(TagTempStructure& updateData, bool isFriend,  bool template_oper, QStringList choices)
{
    updateData.p+=updateData.currentTag.length()  + updateData.tagPart.length();
    if (isFriend && !strncmp(updateData.p, "::", 2))
        updateData.p += 2;
    else
        updateData.s += ((template_oper) ? choices[0] : choices[1]);
}

void Name(TagTempStructure& updateData, QString precomputedName)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    updateData.s += precomputedName;
}

void Tag(TagTempStructure& updateData)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    updateData.s += updateData.currentTag;
}
void ConditionalTag(TagTempStructure& updateData, bool conditional)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    if(conditional)
        updateData.s += QString(" ") + updateData.currentTag;
}
void CppExceptions(TagTempStructure& updateData, OperationData* oper,  QStringList list, BrowserNodeList& nodes)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();

    int index;
    int ne = oper->get_n_exceptions();
    const char * sep = " throw (";

    for (index = 0; index != ne; index += 1)
    {
        updateData.s += sep;
        updateData.s += GenerationSettings::cpp_type(type(oper->get_exception(index).get_type(), list, nodes));
        sep = ", ";
    }

    if (index != 0)
        updateData.s += ')';
    else if (GenerationSettings::cpp_oper_force_throw())
        updateData.s += " throw ()";
}

void CppParamType(TagTempStructure& updateData, QStringList types, QStringList list, BrowserNodeList& nodes )
{
    QRegExp rx("\\d+$");
    rx.indexIn(updateData.currentTag);
    int rank = rx.cap().toInt();
    if (rank < types.size())
        updateData.s += get_cpp_name(the_type(types[rank], list, nodes));
    else {
        updateData.s += "${t";
        updateData.s += QString::number(rank);
        updateData.s += '}';
    }
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
}
void CppParamName(TagTempStructure& updateData, QStringList names )
{
    QRegExp rx("\\d+$");
    rx.indexIn(updateData.currentTag);
    int rank = rx.cap().toInt();
    if (rank < names.size())
        updateData.s += names[rank];
    else {
        updateData.s += "${p";
        updateData.s += QString::number(rank);
        updateData.s += '}';
    }
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
}
void CppParamInit(TagTempStructure& updateData, QStringList values)
{
    QRegExp rx("\\d+$");
    rx.indexIn(updateData.currentTag);
    int rank = rx.cap().toInt();
    if (rank < values.size())
    {
        QString v = values[rank].stripWhiteSpace();

        if (! v.isEmpty())
            updateData.s += " = " + v;
    }
    else {
        updateData.s += "${v";
        updateData.s += QString::number(rank);
        updateData.s += '}';
    }
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
}
void StaticInclude(TagTempStructure& updateData, bool conditional, QString indent)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    if(conditional)
    {
        updateData.s += '\n';
        updateData.s += indent;
    }
    else
        updateData.s += " ";
}
void StereotypeForGetSet(TagTempStructure& updateData)
{
    if(updateData.oper->get_or_set())
    {
        updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
        updateData.s += GenerationSettings::cpp_relationattribute_stereotype(updateData.oper->get_stereotype());
    }
}
void AssociationForGetSet(TagTempStructure& updateData)
{
    if(updateData.oper->get_or_set())
    {
        updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
        updateData.s += GenerationSettings::cpp_type(((BrowserOperation *) updateData.oper->get_browser_node())
                                          ->get_of_association().get_type());
    }
}
void NewLine(TagTempStructure& updateData, QString indent)
{
    updateData.s += *updateData.p++;

    if (*updateData.p && (*updateData.p != '#'))
        updateData.s += indent;
}

void Alias(TagTempStructure& updateData, KeyValuesTable* kvt)
{
    manage_alias(updateData.oper->get_browser_node(), updateData.p, updateData.s, kvt);
}

void ExtractTag(TagTempStructure& temp, QHash<QString, TagData> extractors)
{
    if(extractors.contains(QString(*temp.p)))
    {
        TagData tagData = extractors[QString(*temp.p)];
        if(tagData.tagEnd == QString(""))
        {
            temp.currentTag = QString(*temp.p);
            temp.tagPart =QString(*temp.p);
            return;
        }

        QString  tempString = QString::fromLocal8Bit(temp.p);
        QRegExp rx(QRegExp::escape(tagData.tagEnd));
        int position = rx.indexIn(tempString);
        int tagLength = 0;
        if(position != -1)
            tagLength = position - 1;
        QString tag = QString::fromLocal8Bit(temp.p+tagData.tagStart.length(), tagLength - tagData.tagEnd.length());
        temp.currentTag = tag;
        temp.tagPart = tagData.tagStart + tagData.tagEnd;
    }
}
QString GeneralizeNumbered(QString tag)
{
    return tag.replace(QRegExp("[0-9]+"),"");
}


void SetupManagerStruct(TagManagers::TagTempStructure& tempStruct, OperationData* oper, QString indent, QString& templates, bool& re_template)
{
    // getting some pre-computed data
    QString cl_names;
    QString templates_tmplop;
    QString cl_names_tmplop;

    bool template_oper = oper->is_template_operation(tempStruct.def);
    BrowserClass* container = static_cast<BrowserClass*>(oper->get_browser_node()->parent());
    static_cast<ClassData*>(container->get_data())->get_class_spec(templates, cl_names, templates_tmplop, cl_names_tmplop);

    re_template = !templates.isEmpty() &&
                       insert_template((template_oper) ? templates_tmplop : templates,
                                       tempStruct.p, tempStruct.s, indent);
    QString comment = oper->get_browser_node()->get_comment();
    BrowserNodeList nodes;
    QStringList list;
    BrowserClass::instances(nodes);
    nodes.full_names(list);
    QString name = static_cast<BrowserOperation*>(oper->get_browser_node())->compute_name(oper->get_cpp_name_spec());
    // got all necessary data

    using namespace TagManagers::Cpp;

    tempStruct.oper = oper;
    tempStruct.tagProcessor.insert("comment", std::bind(Comment, std::ref(tempStruct), comment, re_template,templates ));
    tempStruct.tagProcessor.insert("description", std::bind(Description, std::ref(tempStruct), comment, re_template,templates ));
    tempStruct.tagProcessor.insert("inline", std::bind(ConditionalTag, std::ref(tempStruct),oper->get_cpp_inline()));
    tempStruct.tagProcessor.insert("const", std::bind(ConditionalTag, std::ref(tempStruct), oper->get_cpp_const()));
    tempStruct.tagProcessor.insert("volatile", std::bind(ConditionalTag, std::ref(tempStruct), oper->get_is_volatile()));
    tempStruct.tagProcessor.insert("type", std::bind(ReturnType, std::ref(tempStruct), QString(oper->get_return_type().get_type()), list, nodes ));
    tempStruct.tagProcessor.insert("class", std::bind(Class, std::ref(tempStruct), oper->get_cpp_friend(), template_oper,QStringList() << cl_names_tmplop << cl_names ));
    tempStruct.tagProcessor.insert("name", std::bind(Name, std::ref(tempStruct), name));
    tempStruct.tagProcessor.insert("(", std::bind(Tag, std::ref(tempStruct)));
    tempStruct.tagProcessor.insert(")", std::bind(Tag, std::ref(tempStruct)));
    tempStruct.tagProcessor.insert("throw", std::bind(CppExceptions, std::ref(tempStruct), oper, list, nodes ));
    tempStruct.tagProcessor.insert("staticincl", std::bind(StaticInclude, std::ref(tempStruct), oper->get_isa_class_operation(), indent));
    tempStruct.tagProcessor.insert("t", std::bind(CppParamType, std::ref(tempStruct), oper->get_param_types(), list, nodes  ));
    tempStruct.tagProcessor.insert("p", std::bind(CppParamName, std::ref(tempStruct), oper->get_param_names()  ));
    tempStruct.tagProcessor.insert("stereotype", std::bind(StereotypeForGetSet, std::ref(tempStruct)));
    tempStruct.tagProcessor.insert("association", std::bind(AssociationForGetSet, std::ref(tempStruct)));
    tempStruct.tagProcessor.insert("\n", std::bind(NewLine, std::ref(tempStruct), indent));
    tempStruct.tagProcessor.insert("@", std::bind(Alias, std::ref(tempStruct), static_cast<KeyValuesTable*>(0)));
}


QString updated_def(OperationData* oper)
{
    if (oper->get_cpp_default() || oper->get_cpp_delete())
        return "";
    TagManagers::TagTempStructure tempStruct;
    if(!oper->get_is_abstract())
    {


        tempStruct.def = oper->get_cppdef();
        tempStruct.p = tempStruct.def;
        tempStruct.pp = 0;

        tempStruct.indent = "";

        while ((*tempStruct.p == ' ') || (*tempStruct.p == '\t'))
            tempStruct.indent += *tempStruct.p++;
        QString templates;
        bool re_template;
        SetupManagerStruct(tempStruct, oper, tempStruct.indent, templates, re_template);

        TagManagers::Cpp::HashSymbol(tempStruct);

        QHash<QString, TagManagers::TagData> extractors;
        extractors.insert(QString("$"), {QString("${"), QString("}")});
        extractors.insert(QString("@"), {QString("@"), QString("")});
        extractors.insert(QString("\n"), {QString("\n"), QString("")});

        forever
        {
            if(!TagManagers::Cpp::NullValue(tempStruct, re_template, templates, tempStruct.indent))
                break;

            tempStruct.currentTag = QString();
            TagManagers::Cpp::ExtractTag(tempStruct, extractors);
            // GeneralizeNumbered below changes t/p/v{number} into t/p/v.
            // Obviously, I have no desire to riddle tagProcessor with keys like t1,t2,t3,...
            QString generalizedTag = TagManagers::Cpp::GeneralizeNumbered(tempStruct.currentTag);
            //QLOG_INFO() << generalizedTag;
            if(tempStruct.tagProcessor.contains(generalizedTag))
                tempStruct.tagProcessor[generalizedTag]();
            else
                tempStruct.s += *tempStruct.p++;
            //QLOG_INFO() << QString(tempStruct.s);
        }
    }
    return QString(tempStruct.s);
}

}
}
