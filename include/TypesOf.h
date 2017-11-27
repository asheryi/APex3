// 318225851
// Yishay Asher

//
// File of enums which are types of ...
//

#ifndef EX3_TypesOf_H
#define EX3_TypesOf_H

enum Color {
    empty,
    black,
    white
};

enum Error {
    outOfBounds,
    notIntegers,
    notValidMove
};

enum GameStatus {
    whiteWon,
    blackWon,
    noOneWon,
    tie,
    passTurn
};

#endif //EX3_TypesOf_H
