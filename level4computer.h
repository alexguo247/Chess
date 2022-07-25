#ifndef COMPUTER4_H
#define COMPUTER4_H
#include "player.h"
#include "board.h"

class computer4 : public Player
{
public:
    computer4(Board *b, Colour c): Player(b,c) {};
    bool virtual move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

