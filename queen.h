#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "colour.h"
#include "board.h"

class Queen : public Piece
{
public:
    Queen(Colour, int, int);
    bool checkMove(pair<int, int>, Board *);
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif