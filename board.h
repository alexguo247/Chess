#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "textdisplay.h"
#include <vector>
#include <stdbool.h>

class Piece;
class Textdisplay;

class Board
{
    std::vector<std::vector<Piece *>> grid;

public:
    Board();
    Piece *getPiece(int, int);
    void setPiece(Piece *, int, int);
    bool isValid();
    void deletePiece(int, int);
    void clearBoard();
    void printBoard();
    void setup(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
};

#endif
