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
#ifndef CPPTAGMANAGEMENT_H
#define CPPTAGMANAGEMENT_H
#include <QString>
#include <QHash>
#include <functional>
#include <BrowserNode.h>
class OperationData;
class KeyValuesTable;
namespace TagManagers
{
struct TagTempStructure
{
    const char* p;
    const char* pp;
    unsigned rank;
    QString s;
    QString currentTag;
    QString tagPart;
    QString def;
    QString indent;
    OperationData* oper;
    QHash<QString, std::function<QString(TagTempStructure&)> > tagDealer;
    std::function<QString(const char*, TagTempStructure&)> tagPartGetter;
    QHash<QString, std::function<void()> > tagProcessor;
};

struct TagData
{
    QString tagStart;
    //QString tagLimiterLeft;
    //QString tagLimiterRight;
    QString tagEnd;

};

namespace  Cpp
{
void SetupManagerStruct(TagManagers::TagTempStructure& tempStruct, OperationData* oper, QString indent, QString& templates, bool& re_template);
QString updated_def(OperationData* oper);


void Comment(TagTempStructure& updateData, QString commentText, bool re_template, QString templates);
void Description(TagTempStructure& updateData, QString commentText, bool re_template, QString templates);
void HashSymbol(TagTempStructure& updateData);
bool NullValue(TagTempStructure& updateData, bool re_template, QString templates, QString indent);
void ReturnType(TagTempStructure& updateData, QString type, QStringList list, BrowserNodeList& nodes);
void Class(TagTempStructure& updateData, bool isFriend,  bool template_oper, QStringList choices);
void Name(TagTempStructure& updateData, QString precomputedName);
void Tag(TagTempStructure& updateData);
void ConditionalTag(TagTempStructure& updateData, bool conditional);
void CppExceptions(TagTempStructure& updateData, OperationData* oper, QStringList list, BrowserNodeList& nodes);
void CppParamType(TagTempStructure& updateData, QStringList types, QStringList list, BrowserNodeList& nodes );
void CppParamName(TagTempStructure& updateData, QStringList names );
void CppParamInit(TagTempStructure& updateData, QStringList values );
void StaticInclude(TagTempStructure& updateData, bool conditional, QString indent);
void StereotypeForGetSet(TagTempStructure& updateData);
void AssociationForGetSet(TagTempStructure& updateData);
void NewLine(TagTempStructure& updateData, QString indent);
void Alias(TagTempStructure& updateData, KeyValuesTable* kvt);
void ExtractTag(TagTempStructure& temp, QHash<QString, TagData> extractors);
QString GeneralizeNumbered(QString tag);
}
}
#endif // CPPTAGMANAGEMENT_H
