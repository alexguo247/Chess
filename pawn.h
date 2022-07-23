#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "piece.h"

class Board;

class Pawn : public Piece
{
    bool didDoubleMove;

public:
    Pawn(Colour, int, int, bool, bool);
    bool checkMove(std::pair<int, int>, Board &) override;
    std::vector<std::vector<int>> getAttackMoves(Board &, bool) override;
    std::vector<std::vector<int>> getActualMoves(Board &, bool);
    bool hasDoubleMoved();
    void setDidDoubleMove(bool);
};

#endif