#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "textdisplay.h"
#include <vector>
#include <stdbool.h>

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
    void setup(std::vector<vector<int>> &, std::vector<vector<int>> &, pair<int, int> &, pair<int, int> &);
};

#endif
