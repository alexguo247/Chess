#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "colour.h"
#include "board.h"

class Knight : public Piece
{
public:
    Knight(Colour);
    bool checkMove(int, int, int, int, Board *);
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif