#ifndef EX1_ATTACT_H
#define EX1_ATTACT_H


#include "Cell.h"

//abstract class for attack so the board could know which discs it need to flip
class Attack {
public:
    /**
     * indicate if we can call getNext function , aka there is a next cell .
     * @return true if and only if there is a next cell .
     */
    virtual bool hasNext()=0;

    /**
     * @return the next disc position which need to be flip.
     */
    virtual Cell getNext()=0;
};


#endif //EX1_ATTACT_H
