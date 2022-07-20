#ifndef __PAWN_H__
#define __PAWN_H__
#include "colour.h"
#include "board.h"

class Pawn : public Piece
{
    bool hasMoved;

public:
    Pawn(Colour, int, int);
    bool checkMove(int, int, int, int, Board *);
};

#endif