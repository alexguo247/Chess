#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "player.h"

class computer1 : public Player
{
public:
    void virtual move(std::pair<int, int>, std::pair<int, int>);
};

#endif
