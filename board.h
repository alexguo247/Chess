#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdbool.h>

class Piece;

class Board
{
public:
    std::vector<std::vector<Piece *>> grid;
    Board();
    Piece *getPiece(int, int);
    void setPiece(Piece *, int, int);
    bool isValid();
    void print();
    void deletePiece(int, int);
    void clearBoard();
    void printBoard();
    void setup();
};

#endif
