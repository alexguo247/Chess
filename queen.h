#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "colour.h"
#include "piece.h"

class Board;

class Queen : public Piece
{
public:
    Queen(Colour, int, int, bool);
    bool checkMove(std::pair<int, int>, Board &);
    std::vector<std::vector<int>> getAttackMoves(Board &);
};

#endif