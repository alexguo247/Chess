#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "colour.h"

class Player
{
protected:
    Board *b;
    Colour c;
    bool inCheck;

public:
    Player(Board *, Colour);
    virtual ~Player(); 
    bool virtual move(Board *, std::pair<int, int>, std::pair<int, int>, char) = 0;
};

#endif
