#ifndef __KING_H__
#define __KING_H__
#include "colour.h"
#include "board.h"

class King : public Piece
{
public:
    King(Colour, int, int);
    bool checkMove(std::pair<int, int>, Board *) override;
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif