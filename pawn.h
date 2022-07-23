#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "piece.h"

class Board;

class Pawn : public Piece
{

public:
    Pawn(Colour, int, int);
    bool checkMove(std::pair<int, int>, Board *);
    std::vector<std::vector<int>> getAttackMoves(Board *);
};

#endif