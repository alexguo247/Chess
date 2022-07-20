#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player
{
public:
    int move(std::pair<int, int>, std::pair<int, int>) override;
};

#endif;