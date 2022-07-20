#ifndef __KING_H__
#define __KING_H__
#include "colour.h"
#include "board.h"

class King : public Piece
{
public:
    King(Colour);
    bool checkMove(int, int, int, int, Board *);
};

#endif