

#include <q3ptrdict.h>
//Added by qt3to4:
#include <functional>
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

namespace TagManagers
{
namespace  Cpp
{
bool ManageNullValue(UpdateCppData& updateData, bool re_template, QString templates, QString indent)
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
    return true;
}
void ManageComment(UpdateCppData& updateData, QString commentText, bool re_template, QString templates)
{
    if (!manage_comment(commentText, updateData.p, updateData.pp,
                        GenerationSettings::cpp_javadoc_style())
            && re_template)
        updateData.s += templates;
}
void ManageDescription(UpdateCppData& updateData, QString commentText, bool re_template, QString templates)
{
    if (!manage_description(commentText, updateData.p, updateData.pp) && re_template)
        updateData.s += templates;
}
void ManageHashSymbol(UpdateCppData& updateData)
{
    updateData.s += updateData.indent;
}

void ManageReturnType(UpdateCppData& updateData, QString type, QStringList list, BrowserNodeList& nodes)
{
    int rank; //get rank
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
	updateData.s += get_cpp_name(the_type(type.stripWhiteSpace(),
						   list, nodes));
}
void ManageClass(UpdateCppData& updateData, bool isFriend,  bool template_oper, QStringList choices)
{
    updateData.p+=updateData.currentTag.length()  + updateData.tagPart.length();
    if (isFriend && !strncmp(updateData.p, "::", 2))
        updateData.p += 2;
    else
        updateData.s += ((template_oper) ? choices[0] : choices[1]);
}

void ManageName(UpdateCppData& updateData, QString precomputedName)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    updateData.s += precomputedName;
}

void ManageTag(UpdateCppData& updateData)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    updateData.s += updateData.currentTag;
}
void ManageConditionalTag(UpdateCppData& updateData, bool conditional)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    if(conditional)
        updateData.s += QString(" ") + updateData.currentTag;
}
void ManageCppExceptions(UpdateCppData& updateData, HavekeyValueData exceptions, QStringList list, BrowserNodeList& nodes)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();

    int index;
    int ne = exceptionCount;
    const char * sep = " throw (";

    for (index = 0; index != ne; index += 1)
    {
        updateData.s += sep;
        updateData.s += GenerationSettings::cpp_type(type(exceptions[index], list, nodes));
        sep = ", ";
    }

    if (index != 0)
        updateData.s += ')';
    else if (GenerationSettings::cpp_oper_force_throw())
        updateData.s += " throw ()";
}

void ManageCppParamType(UpdateCppData& updateData, QStringList types, QStringList list, BrowserNodeList& nodes )
{
    if (rank < types.size())
        updateData.s += get_cpp_name(the_type(types[rank], list, nodes));
    else {
        updateData.s += "${t";
        updateData.s += QString::number(rank);
        updateData.s += '}';
    }
}
void ManageCppParamName(UpdateCppData& updateData, QStringList names )
{
    if (rank < names.size())
        updateData.s += names[rank];
    else {
        updateData.s += "${p";
        updateData.s += QString::number(rank);
        updateData.s += '}';
    }
}
void ManageCppParamInit(UpdateCppData& updateData, QStringList values)
{
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
}
void ManageStaticInclude(UpdateCppData& updateData, bool conditional, QString indent)
{
    updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
    if(conditional)
    {
        updateData.s += '\n';
        updateData.s += indent;
    }
    else
        updateData.s += ' ';
}
void ManageStereotypeForGetSet(UpdateCppData& updateData)
{
    if(updateData.oper->get_or_set())
    {
        updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
        updateData.s += GenerationSettings::cpp_relationattribute_stereotype(updateData.oper->get_stereotype());
    }
}
void ManageAssociationForGetSet(UpdateCppData& updateData)
{
    if(updateData.oper->get_or_set())
    {
        updateData.p+=updateData.currentTag.length() + updateData.tagPart.length();
        updateData.s += GenerationSettings::cpp_type(((BrowserOperation *) updateData.oper->get_browser_node())
                                          ->get_of_association().get_type());
    }
}
void ManageNewLine(UpdateCppData& updateData, QString indent)
{
    updateData.s += *updateData.p++;

    if (*updateData.p && (*updateData.p != '#'))
        updateData.s += indent;
}

void ManageAlias(UpdateCppData& updateData, QString indent)
{
    updateData.s += *updateData.p++;

    if (*updateData.p && (*updateData.p != '#'))
        updateData.s += indent;
}
}
}
