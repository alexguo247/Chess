#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "player.h"
#include "board.h"

class computer1 : public Player
{
public:
    computer1(Board *b, Colour c): Player(b,c) {};
    bool virtual move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

