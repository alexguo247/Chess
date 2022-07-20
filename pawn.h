#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "board.h"

class Pawn : public Piece
{
    bool hasMoved;

public:
    Pawn(Colour);
    bool checkMove(int, int, int, int, Board *);
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif