#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include "board.h"

class Rook : public Piece
{
public:
    Rook(Colour, int, int);
    bool checkMove(pair<int, int>, Board *) override;
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif