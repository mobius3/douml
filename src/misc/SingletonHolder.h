#ifndef TREEFILTER_SINGLETONHOLDER_H
#define TREEFILTER_SINGLETONHOLDER_H


#include "include/ArmCommonClasses_global.h"


namespace TreeFilter {

template<typename T>
struct An 
{
    inline An() { clear(); };

    inline T * operator ->() { return get0(); };

    inline const T * operator ->() const { return get0(); };

    inline void operator =(T * t) { data = t; };

    inline bool isEmpty() const { return data == 0; };

    inline void clear() { data = 0; };

    inline void init() { if (isEmpty()) reinit(); };

    inline void reinit() { anFill(*this); };

    inline T * getData() {
            const_cast<An*>(this)->init();
            return data;
        };


  private:
    inline T * get0() const {
            const_cast<An*>(this)->init();
            return data;
        };

     T * data;
};

} // namespace TreeFilter
#endif
