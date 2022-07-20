#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "textdisplay.h"
#include <vector>
#include <set>
#include <stdbool.h>
#include <set>

class Board
{
    Textdisplay *td;
    std::vector<std::vector<Piece *>> grid;

public:
    Piece *getPiece(int, int);
    void setPiece(Piece *, int, int);
    bool isValid();
    Board();
    void clearBoard();
    void setup(std::set<pair<int, int>> &, std::set<pair<int, int>> &, pair<int, int> &, pair<int, int> &);
};

#endif

