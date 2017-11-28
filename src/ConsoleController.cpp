#include "../include/ConsoleController.h"
#include <limits>

Cell *ConsoleController::getLandingPoint() const {
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

int ConsoleController::getMenuSelection() const {
    int selection;
    std::cin >> selection ;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(numeric_limits<int>::max(), '\n');
        return -1;
    }
    return selection;
}