
#include "UmlActivityControlNodeClasses.h"
//Added by qt3to4:
#include <Q3CString>

Q3CString UmlInitialActivityNode::sKind()
{
    return "initial activity node";
}

Q3CString UmlFlowFinalActivityNode::sKind()
{
    return "flow final";
}

Q3CString UmlActivityFinalActivityNode::sKind()
{
    return "activity final";
}

Q3CString UmlDecisionActivityNode::sKind()
{
    return "decision activity node";
}

Q3CString UmlMergeActivityNode::sKind()
{
    return "merge activity node";
}

Q3CString UmlForkActivityNode::sKind()
{
    return "fork activity node";
}

Q3CString UmlJoinActivityNode::sKind()
{
    return "join activity node";
}

