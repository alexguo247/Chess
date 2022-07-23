#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "type.h"
#include "colour.h"
#include <stdbool.h>

class Piece;

class Board
{
public:
    std::vector<std::vector<Piece *>> grid;
    Board();
    Piece *getPiece(int, int);
    void setOrCreatePiece(Piece *, int, int, bool, Type, Colour);
    bool isValid();
    Type getTypeChar(char);
    char getCharType(Piece *);
    void print();
    bool move(std::pair<int, int>, std::pair<int, int>, char); // false if error
    void deletePiece(int, int);
    void clearBoard();
    void setup();
};

#endif
