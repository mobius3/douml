#ifndef _UMLSTATE_H
#define _UMLSTATE_H


#include "UmlBaseState.h"
#include "UmlStateItem.h"
#include <q3cstring.h>
#include "UmlClass.h"

class UmlState : public UmlBaseState, public UmlStateItem
{
public:
    //  the constructor, do not call it yourself !!!!!!!!!!
    UmlState(void * id, const Q3CString & s)
        : UmlBaseState(id, s), _has_initial(FALSE), _has_completion(FALSE), _class(0) {
    }

    bool isLeaf();

    //  indicate that the state has an initial pseudo state
    //  for check, don't return on error
    void hasInitial();

    //  return the class implementing the state

    UmlClass * assocClass() const;

    //  the path to the instance of the class managing the state

    Q3CString path() const;

    //  the path of the state to be produced in debug trace
    Q3CString prettyPath() const;

    bool inside(UmlState * other);

    //  perform initializations before generation
    virtual void init(UmlClass * mother, Q3CString path, Q3CString pretty_path, UmlState * state);

    //  to indicate that the state has a completion

    void setHasCompletion();

    //  return TRUE if the state as completion

    bool hasCompletion();

    bool needCreate();

    //  entry point for the state machine generation
    virtual void generate();

    //  generate all concerning the state
    virtual void generate(UmlClass * machine, UmlClass * anystate, UmlState * state);


protected:
    bool _has_initial;

    bool _has_completion;

    //  the class implementing the state
    UmlClass * _class;

    //  the path from the machine up to the class instance associated
    //  to the state.
    Q3CString _path;

    //  the path from the machine up to the class instance associated
    //  to the state.
    Q3CString _pretty_path;

};

inline UmlClass * UmlState::assocClass() const
{
    return _class;
}

inline Q3CString UmlState::path() const
{
    return _path;
}

inline Q3CString UmlState::prettyPath() const
{
    return _pretty_path;
}

inline void UmlState::setHasCompletion()
{
    _has_completion = TRUE;
}

inline bool UmlState::hasCompletion()
{
    return _has_completion;
}

#endif
