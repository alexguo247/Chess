#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "board.h"

class Pawn : public Piece
{
    bool hasMoved;

public:
    Pawn(Colour, int, int);
    bool checkMove(std::pair<int, int>, Board *);
    std::vector<std::vector<int>> getAttackMoves(Board *);
};

#endif