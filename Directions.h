// 318225851
// Yishay Asher

#ifndef EX2_DIRECTIONS_H
#define EX2_DIRECTIONS_H


#include "Cell.h"

// Directions class , used for better looping through directions (with operator overloading)


class Directions {
public:
    static const Cell left;
    static const Cell right;
    static const Cell up;
    static const Cell down;

    static const Cell upLeft;
    static const Cell downLeft;
    static const Cell upRight;
    static const Cell downRight;

    static const Cell allDirections[8];
};


#endif //EX2_DIRECTIONS_H
