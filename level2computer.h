#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "player.h"
#include "board.h"

class Computer2 : public Player
{
public:
    Computer2(Board *b, Colour c): Player(b,c) {};
    bool move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif
