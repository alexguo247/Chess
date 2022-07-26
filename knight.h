#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "colour.h"
#include "piece.h"

class Board;

class Knight : public Piece
{
public:
    Knight(Colour, int, int, bool);
    bool checkMove(std::pair<int, int>, Board &) override;
    std::vector<std::vector<int>> getAttackMoves(Board &, int) override;
};

#endif
