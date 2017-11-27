#ifndef EX1_ATTACT_H
#define EX1_ATTACT_H


#include "Cell.h"
//abstract class for attack so the board could know which discs it need to flip
class Attack {
public:
    /*****************************************************************************
    *function name:hasNext:indicate if we can call getNext function
    * duplicates.
    *NOTE::indicate if we can call getNext function
    * duplicates.
    *NOTE:
    virtual bool hasNext()=0;
    virtual bool hasNext()=0;
    *operation function
    /*****************************************************************************
    *function name:getNext
    *operation function:return the next disc position which need to be flip.
    * duplicates.
    *NOTE:
    *****************************************************************************/
    virtual Cell getNext()=0;
};


#endif //EX1_ATTACT_H
