#ifndef _UMLBASEITEM_H
#define _UMLBASEITEM_H


#include "anItemKind.h"
#include "misc/mystr.h"
#include <q3ptrvector.h>
#include <q3dict.h>
#include <q3ptrdict.h>
#include "OnInstanceCmd.h"
#include "aVisibility.h"
#include "aDirection.h"

class UmlItem;
class UmlTypeSpec;

// Base class of all the classes representing browser's objects.
//
// In the API all for each 'system' class exists a 'user' class
// under your responsability which inherits the 'system' class.
//
// You do not have to change the 'system' classes, place your
// attributes and operations in the corresponding 'user' classes :
// all the instances made by the 'system' classes are instance of
// the corresponding 'user' classes.
//
// You must never create or delete yourself a class of the API,
// use the Create operation defined in the 'system' classes.
//
// To not allow you to access to the 'system' attributes or to
// call 'system' internal operations even by error, the 'system' internal
// parts are declared 'private' rather than 'public' or 'protected'.
class UmlBaseItem
{
public:
    // return a constant identifier, it is unique within a given
    // kind of element (two classes can't have the same identifiers, but
    // a class and a component may have the same identifier)
    // except for the diagrams (a class diagram can't have the identifier
    // of a component diagram)
    int getIdentifier();

    // returns the kind of the item
    virtual anItemKind kind() = 0;

    // returns the name
    const WrapperStr & name() {
        return _name;
    };

    // to set the name
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    virtual bool set_Name(const WrapperStr & s);

    // returns the stereotype
    const WrapperStr & stereotype();

    // to set the stereotype
    //  On error return FALSE in C++, produce a RuntimeException in Java
    virtual bool set_Stereotype(const WrapperStr & s);

    // returns the description
    const WrapperStr & description();

    // to set the description
    //  On error return FALSE in C++, produce a RuntimeException in Java
    bool set_Description(const WrapperStr & s);

    // returns the parent (0/null if it is applied on the project itself),
    // to go all over the browser tree
    UmlItem * parent();

    // returns (in Java : a copy of) the children list, to go all over the browser tree
    // NOTE : RETURN RFE ONLY HERE, too dangerous for user use
    const Q3PtrVector<UmlItem> & children();

    // return TRUE if the children exist and are visible (independently
    // of the scroll bar) in the browser, else FALSE
    bool childrenVisible();

    // open the item in the browser (its children are visible) if y is TRUE,
    // else close it (its children are not visible). May be applied on items
    // without children. The item is also selected in the browser, so
    // set_ChildrenVisible(childrenVisible()) is the right way to select the item
    // in the browser.
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_childrenVisible(bool y);

    // In C++, in case the key specified by 'k' exist for the current
    // object, the string 'v' is modified which the associated value
    // and TRUE is returned, else returns FALSE.
    //
    // In Java return the value associated with the key specified by 'k'
    // for the current object, null in case the property doesn't
    // exist.
    //
    // These properties may be edited through the object dialog last tab
    // named 'user'
    bool propertyValue(const WrapperStr & k, WrapperStr & v);

    // to set (may be insert a new) the value 'v' associated to the key 'k'
    //
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_PropertyValue(const WrapperStr & k, const WrapperStr & v);

    // returns all the properties of the object through (in Java a copy of) a dictionnary

    const Q3Dict<QString> properties();

    // If the parameter is null, move the current item to be
    // the first child of its parent. Else the current item and
    // the parameter must have the same parent, the current item
    // is moved to be just after the parameter.
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool moveAfter(const UmlItem * x);

    //  Returns the absolute path name of the file memoring the Item.
    //  In general an item is saved in a file associated to its package,
    //  the exceptions are :
    //
    //  - the body of the operations of a class which definition contains the
    //     keyword '{$body}'. This path name is returned when you apply
    //     supportFile on any operation of the class.
    //
    //  - the drawing of the diagrams, this path name is returned when
    //     you apply supportFile on the diagram.
    //
    //  - the configuration of the tools edited throw the entry 'Tools Settings' of
    //     the menu Tools is saved in the file 'tools'
    //
    //  - the configuration of the '#include' and 'using' forms associated to the
    //    external type and edited through the last C++ tab of the
    //    'Generation Settings' dialog is saved in the file 'cpp_includes'
    //
    //  - the configuration of the 'imports' forms associated to the external
    //    types and edited through the last Java tab of the 'Generation Settings'
    //    dialog is saved in the file 'java_imports'
    //
    //  - the configuration of the '#include' forms associated to the
    //    external type and edited through the last Idl tab of the
    //    'Generation Settings' dialog is saved in the file 'idl_includes'
    //
    WrapperStr supportFile();

    // return TRUE in case the item may be modified, i.e. it is not
    // an API base 'plug-out' class and the corresponding file(s) are not
    // read-only.
    bool isWritable();

    //  Apply asynchronously the tool on the item, returns an identifier to call isToolDone()
    int apply(WrapperStr cmd);

    //return TRUE in case the item is marked
    bool isMarked();

    //  to mark/unmark the current item. The project cannot marked
    // On error return FALSE in C++, produce a RuntimeException in Java
    bool set_isMarked(bool y);

    //  Returns the items referencing the current one.
    //  The result may contains UmlAttribute, UmlRelations, UmlNcRelations,
    //  UmlOperation (their bodies are not taken into account) , UmlClass
    //  and UmlComponents.
    const Q3PtrVector<UmlItem> referencedBy();

    // to unload the object to free memory, it will be reloaded automatically
    // if needed. Recursively done for the sub items if 'rec' is TRUE.
    //
    // if 'del' is true the sub items are deleted in C++, and removed from the
    // internal dictionnary in C++ and Java (to allow it to be garbaged),
    // you will have to call Children() to re-access to them
    virtual void unload(bool rec = FALSE, bool del = FALSE);

    //  'id' is an identifier returned by apply(), indicates if the tool is still running
    static bool isToolRunning(int id);

    //remove the element from the model, use it carefully because\n"
    // after that the element can't be used anymore by the plug-out\n"
    // On error : return FALSE in C++, produce a RuntimeException in Java
    bool deleteIt();

    // not in plug-outs managed through bouml
    bool moveIn(UmlItem * x);
    void setUser(unsigned uid);
    static UmlItem * from_id(unsigned uid, anItemKind);

    static const Q3PtrVector<UmlItem> markedItems();

    friend class UmlBaseClassItem;
    friend class UmlBaseAttribute;
    friend class UmlBaseClass;
    friend class UmlBaseClassInstance;
    friend class UmlBaseClassDiagram;
    friend class UmlBaseClassView;
    friend class UmlBaseCollaborationDiagram;
    friend class UmlBaseArtifact;
    friend class UmlBaseComponentDiagram;
    friend class UmlBaseComponentView;
    friend class UmlBaseDeployment;
    friend class UmlBaseDeploymentDiagram;
    friend class UmlBaseDeploymentView;
    friend class UmlBaseNode;
    friend class UmlBaseOperation;
    friend class UmlBasePackage;
    friend class UmlBaseRelation;
    friend class UmlBaseNcRelation;
    friend class UmlBaseSequenceDiagram;
    friend class UmlBaseUseCase;
    friend class UmlBaseUseCaseDiagram;
    friend class UmlBaseUseCaseView;
    friend class UmlBaseDiagram;
    friend class UmlBaseFormalParameter;
    friend class UmlBaseActualParameter;
    friend class UmlCom;
    friend class UmlBaseClassMember;
    friend class UmlBaseExtraClassMember;
    friend class UmlBaseComponent;

private:
    bool _defined;

    bool _marked;

    void * _identifier;

    int _modeler_id;

    WrapperStr _name;

    //  Note : protected in Java for internal reason, but do NOT
    //  access to this field yourself !
    WrapperStr _stereotype;

    WrapperStr _description;

    UmlItem * _parent;

    Q3PtrVector<UmlItem> * _children;

    Q3Dict<QString> _dict;

    static Q3PtrDict<UmlItem> _all;


protected:
    //internal, do NOT use it

    void read_if_needed_();

    //internal, do NOT use it

    UmlItem * create_(anItemKind k, const char * s);

    //internal, do NOT use it

    virtual void read_uml_();

#ifdef WITHCPP
    //internal, do NOT use it

    virtual void read_cpp_();
#endif

#ifdef WITHJAVA
    //internal, do NOT use it

    virtual void read_java_();
#endif

#ifdef WITHPHP
    //internal, do NOT use it

    virtual void read_php_();
#endif

#ifdef WITHPYTHON
    //internal, do NOT use it

    virtual void read_python_();
#endif

#ifdef WITHIDL
    //internal, do NOT use it

    virtual void read_idl_();
#endif

    //internal, do NOT use it

    void read_children_();

    //internal, do NOT use it

    void reread_children_if_needed_();

    //internal, do NOT use it

    bool set_it_(bool & r, bool v, OnInstanceCmd cmd);

    //internal, do NOT use it

    bool set_it_(aVisibility & r, aVisibility v, OnInstanceCmd cmd);

    //internal, do NOT use it

    bool set_it_(aDirection & r, aDirection v, OnInstanceCmd cmd);

    //internal, do NOT use it

    bool set_it_(WrapperStr & r, const char * v, OnInstanceCmd cmd);

    //internal, do NOT use it

    bool set_it_(UmlTypeSpec & r, const UmlTypeSpec & t, OnInstanceCmd cmd);

    //internal, do NOT use it

    static UmlItem * read_();


public:
    // the constructor, do not call it yourself !
    UmlBaseItem(void * id, const WrapperStr & n);

    // the destructor, do not delete objects yourself !!!!!!!!!!
    virtual ~UmlBaseItem();

    friend class UmlBaseState;
    friend class UmlBaseStateDiagram;
    friend class UmlBaseTransition;
    friend class UmlBaseRegion;
    friend class UmlBaseStateAction;
    friend class UmlBaseInitialPseudoState;
    friend class UmlBaseEntryPointPseudoState;
    friend class UmlBaseFinalState;
    friend class UmlBaseTerminatePseudoState;
    friend class UmlBaseExitPointPseudoState;
    friend class UmlBaseDeepHistoryPseudoState;
    friend class UmlBaseShallowHistoryPseudoState;
    friend class UmlBaseJunctionPseudoState;
    friend class UmlBaseChoicePseudoState;
    friend class UmlBaseForkPseudoState;
    friend class UmlBaseJoinPseudoState;
    friend class UmlBaseObjectDiagram;
    friend class UmlBaseActivity;
    friend class UmlBaseActivityDiagram;
    friend class UmlBaseActivityNode;
    friend class UmlBaseFlow;
    friend class UmlBaseActivityRegion;
    friend class UmlBaseExpansionRegion;
    friend class UmlBaseInterruptibleActivityRegion;
    friend class UmlBaseActivityAction;
    friend class UmlBaseSendObjectAction;
    friend class UmlBaseUnmarshallAction;
    friend class UmlBaseOnSignalAction;
    friend class UmlBaseSendSignalAction;
    friend class UmlBaseBroadcastSignalAction;
    friend class UmlBaseValueSpecificationAction;
    friend class UmlBaseOpaqueAction;
    friend class UmlBaseAcceptEventAction;
    friend class UmlBaseCallOperationAction;
    friend class UmlBaseCallBehaviorAction;
    friend class UmlBaseAccessVariableValueAction;
    friend class UmlBaseClearVariableValueAction;
    friend class UmlBaseReadVariableValueAction;
    friend class UmlBaseWriteVariableValueAction;
    friend class UmlBaseAddVariableValueAction;
    friend class UmlBaseRemoveVariableValueAction;
    friend class UmlBaseReduceAction;
    friend class UmlBaseRaiseExceptionAction;
    friend class UmlBaseTestIdentityAction;
    friend class UmlBaseDestroyObjectAction;
    friend class UmlBaseCreateObjectAction;
    friend class UmlBaseReplyAction;
    friend class UmlBaseAcceptCallAction;
    friend class UmlBaseActivityControlNode;
    friend class UmlBaseInitialActivityNode;
    friend class UmlBaseFlowFinalActivityNode;
    friend class UmlBaseActivityFinalActivityNode;
    friend class UmlBaseDecisionActivityNode;
    friend class UmlBaseMergeActivityNode;
    friend class UmlBaseForkActivityNode;
    friend class UmlBaseJoinActivityNode;
    friend class UmlBaseActivityObject;
    friend class UmlBaseExpansionNode;
    friend class UmlBasePinParameter;
    friend class UmlBaseActivityPin;
    friend class UmlBaseActivityParameter;
    friend class UmlBaseParameterSet;
    friend class UmlBaseActivityPartition;
};

#endif
