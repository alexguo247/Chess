#ifndef COMPUTER3_H
#define COMPUTER3_H
#include "player.h"
#include "board.h"

class Computer3 : public Player
{
public:
    Computer3(Board *b, Colour c): Player(b,c) {};
    bool move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

