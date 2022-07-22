#ifndef __KING_H__
#define __KING_H__
#include "colour.h"
#include "piece.h"

class Board;

class King : public Piece
{
public:
    King(Colour, int, int);
    bool checkMove(std::pair<int, int>, Board *) override;
    std::vector<std::vector<int>> getAttackMoves(Board &) override;
};

#endif