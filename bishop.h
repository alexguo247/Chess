#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include "board.h"

class Bishop : public Piece
{
public:
    Bishop(Colour);
    bool checkMove(int, int, int, int, Board *);
    std::vector<std::pair<int, int>> getAttackMoves(Board *);
};

#endif