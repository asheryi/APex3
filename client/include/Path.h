

#ifndef EX1_PATH_H
#define EX1_PATH_H


#include "Cell.h"
#include <vector>

using namespace std;

class Path {
private:
    //player actual landing
    Cell *landing;
    vector<Cell *> directions;
    vector<Cell *> stopCells;

    int abs(int x) const;

public:
    /*****************************************************************************
    *function name:Path
    *operation function:constructor gets start point,the position of the the first
     * disc, and the direction the disc attack.
    *NOTE:
    *****************************************************************************/
    Path(Cell *landing);

    /*****************************************************************************
    *function name:setLanding
    *operation function:set the landing point.
    *NOTE:
    *****************************************************************************/
    void insertMove(Cell *direction, Cell *stopCell);    /*****************************************************************************
    *function name:getStartAttackFrom
    *operation function:get the point from where to start the attack.
    *NOTE:
    *****************************************************************************/
    Cell *getStopCell(int index) const;

    /*****************************************************************************
    *function name:getLanding
    *operation function:get the landing point.
    *NOTE:
    *****************************************************************************/
    Cell getLanding() const;

    /*****************************************************************************
    *function name:getDirection
    *operation function:get the direction the disc attack.
    *NOTE:
    *****************************************************************************/
    Cell *getDirection(int index) const;

    /*
     * @return the amount of disks to eat.
     */
    int length() const;

    /*
     * @return the amounts of eating directions.
     */
    int numberOfEatingDirections() const;

    /*
     * Copy constructor.
     * @param other- Path-to be copy.
     */
    Path(const Path &other);

    ~Path();
};


#endif //EX1_PATH_H
