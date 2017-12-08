#include "../include/StandardAttack.h"

StandardAttack::StandardAttack(const Path &path_) : path(path_), curr(path_.getLanding()), index(0) {
}

bool StandardAttack::hasNext() {
    //TODO:change 0 to loop
    if (index < path.numberOfEatingDirections()) {
        // ??? path.getStopCell(index) != 0 && path.getDirection(index) != 0 &&
        if ((curr - *path.getDirection(index)) != *path.getStopCell(index)) {
            return true;
        } else {
            index++;
            curr = path.getLanding();
            if (index < path.numberOfEatingDirections()) {
                curr += *path.getDirection(index);
            }
            return hasNext();
        }
    } else return false;
}

Cell StandardAttack::getNext() {
    curr += *path.getDirection(index);
    return (curr - *path.getDirection(index));
}