#ifndef COMPUTER3_H
#define COMPUTER3_H
#include "player.h"
#include "board.h"

class computer3 : public Player
{
public:
    computer3(Board *b, Colour c): Player(b,c) {};
    bool virtual move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

