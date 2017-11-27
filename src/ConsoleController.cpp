#include "../include/ConsoleController.h"
#include <limits>
Cell* ConsoleController::getLandingPoint() const {
    int row, col;
    char comma;
    std::cin >> row >> comma >> col;
    if (std::cin.fail() || comma != ',') {
        std::cin.clear();
        std::cin.ignore(numeric_limits<int>::max(), '\n');
        return NULL;
    }
    return new Cell(row, col);

}