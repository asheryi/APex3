//
// Created by Brain on 11/11/2017.
//

#ifndef EX1_STANDARDATTACT_H
#define EX1_STANDARDATTACT_H


#include "Attack.h"
#include "Path.h"

class StandardAttack : public Attack{
private:
    Cell curr;
    Path path;
    int index;
public:
    StandardAttack(const Path& path_);
    bool hasNext();
    Cell getNext();
};


#endif //EX1_STANDARDATTACT_H
