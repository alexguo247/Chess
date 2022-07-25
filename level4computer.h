#ifndef COMPUTER4_H
#define COMPUTER4_H
#include "player.h"
#include "board.h"

class Computer4 : public Player
{
public:
    Computer4(Board *b, Colour c): Player(b,c) {};
    bool move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

