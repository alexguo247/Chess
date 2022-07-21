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
    ~Player(); 
    void virtual move(std::pair<int, int>, std::pair<int, int>) = 0;
};

#endif