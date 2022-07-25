#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
class Board;

class Bishop : public Piece
{
public:
    Bishop(Colour, int, int, bool);
    bool checkMove(std::pair<int, int>, Board &) override;
    std::vector<std::vector<int>> getAttackMoves(Board &, int) override;
};

#endif