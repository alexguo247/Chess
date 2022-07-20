#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "colour.h"
#include "board.h"

class Knight : public Piece
{
public:
    Knight(Colour, int, int);
    bool checkMove(std::pair<int, int>, Board *);
};

#endif