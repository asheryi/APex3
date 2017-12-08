

#include "../../include/Directions.h"

const Cell Directions::left(0, -1);
const Cell Directions::right(0, 1);
const Cell Directions::up(1, 0);
const Cell Directions::down(-1, 0);

const Cell Directions::upLeft(1, -1);
const Cell Directions::upRight(1, 1);
const Cell Directions::downLeft(-1, -1);
const Cell Directions::downRight(-1, 1);

const Cell Directions::allDirections[] = {left, right, up, down, upLeft, upRight, downLeft, downRight};