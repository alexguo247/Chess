#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "piece.h"

class Board;

class Pawn : public Piece
{

public:
    int doubleMove;
    Pawn(Colour, int, int, bool, int);
    bool checkMove(std::pair<int, int>, Board &) override;
    std::vector<std::vector<int>> getAttackMoves(Board &, int) override;
    std::vector<std::vector<int>> getActualMoves(Board &, int);
    bool hasDoubleMoved();
    void setDoubleMove(int);
};

#endif
