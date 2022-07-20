#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include "board.h"

class Bishop : public Piece
{
public:
    Bishop(Colour, int, int);
    bool checkMove(int, int, int, int, Board *);
};

#endif