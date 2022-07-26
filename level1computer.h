#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "player.h"
#include "board.h"

class Computer1 : public Player
{
public:
    Computer1(Board *b, Colour c): Player(b,c) {};
    bool move(Board *, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

